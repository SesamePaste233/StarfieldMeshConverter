import bpy

import utils_common as utils

import numpy as np

_data_type_element_prop_ = {
    "FLOAT_VECTOR": (3, np.float32, "vector"),
    "FLOAT_COLOR": (4, np.float32, "color"),
}

class MorphAttrFactory:
	def __init__(self, abbr:str, domain:str, type:str, from_mesh_data_fn=None, to_mesh_data_fn=None, name_fn=None, sk_name_fn=None, abbr_name_fn=None):
		self.abbr = abbr
		self.domain = domain
		self.type = type

		if not name_fn:
			self.name_fn = lambda shapekey_name: f"{self.abbr}_{shapekey_name}"
		else:
			self.name_fn = name_fn

		if not sk_name_fn:
			self.sk_name_fn = lambda attr_name: attr_name[len(self.abbr) + 1:]
		else:
			self.sk_name_fn = sk_name_fn

		if not abbr_name_fn:
			self.abbr_name_fn = lambda attr_name: attr_name[:attr_name.find("_")]
		else:
			self.abbr_name_fn = abbr_name_fn

		if not from_mesh_data_fn:
			self.from_mesh_data_fn = lambda attr, shapekey_name, mesh: None
		else:
			self.from_mesh_data_fn = from_mesh_data_fn

		if not to_mesh_data_fn:
			self.to_mesh_data_fn = lambda attr, shapekey_name, mesh: None
		else:
			self.to_mesh_data_fn = to_mesh_data_fn

	def create(self, mesh:bpy.types.Mesh, shapekey_name:str, replace = True) -> bpy.types.Attribute:
		if shapekey_name not in mesh.shape_keys.key_blocks:
			return None

		if self.name_fn(shapekey_name) not in mesh.attributes:
			mesh.attributes.new(name=self.name_fn(shapekey_name), domain=self.domain, type=self.type)
		elif replace:
			mesh.attributes.remove(mesh.attributes[self.name_fn(shapekey_name)])
			mesh.attributes.new(name=self.name_fn(shapekey_name), domain=self.domain, type=self.type)

		return mesh.attributes[self.name_fn(shapekey_name)]

	def validate(self, mesh:bpy.types.Mesh, shapekey_name:str, remove_invalid = True, create_if_invalid = False) -> None|bpy.types.Attribute:
		if self.name_fn(shapekey_name) in mesh.attributes:
			if shapekey_name not in mesh.shape_keys.key_blocks:
				if remove_invalid:
					mesh.attributes.remove(mesh.attributes[self.name_fn(shapekey_name)])
					return None
				else:
					return None
		
			attr = mesh.attributes[self.name_fn(shapekey_name)]
			if attr.domain == self.domain and attr.data_type == self.type:
				return attr
			elif remove_invalid and not create_if_invalid:
				mesh.attributes.remove(attr)
				return None
			elif create_if_invalid:
				return self.create(mesh, shapekey_name, replace=True)
			else:
				return None
		elif create_if_invalid:
			return self.create(mesh, shapekey_name)
		else:
			return None
		
	def get(self, mesh:bpy.types.Mesh, shapekey_name:str, create_if_not_exist = False) -> bpy.types.Attribute:
		return self.validate(mesh, shapekey_name, remove_invalid=False, create_if_invalid=create_if_not_exist)
	
	def validate_all(self, mesh:bpy.types.Mesh, remove_invalid = True):
		for attr in mesh.attributes:
			if self.abbr == self.abbr_name_fn(attr.name):
				sk_name = self.sk_name_fn(attr.name)
				if sk_name not in mesh.shape_keys.key_blocks:
					if remove_invalid:
						mesh.attributes.remove(attr)
						print(f"Shapekey {sk_name} not found. Removing attribute {attr.name}")
					else:
						print(f"Shapekey {sk_name} not found.")
				else:
					if attr.domain != self.domain or attr.data_type != self.type:
						if remove_invalid:
							mesh.attributes.remove(attr)
							print(f"Attribute {attr.name} is invalid. Removing.")
						else:
							print(f"Attribute {attr.name} is invalid.")
	
	@utils.timer
	def from_mesh_data(self, mesh:bpy.types.Mesh, shapekey_name:str) -> None:
		attr = self.validate(mesh, shapekey_name, remove_invalid=True, create_if_invalid=True)
		if not attr:
			print(f"Attribute {self.name_fn(shapekey_name)} not found or invalid.")
			return
		
		self.from_mesh_data_fn(attr, shapekey_name, mesh)

	def to_mesh_data(attr, mesh:bpy.types.Mesh, shapekey_name:str) -> None:
		pass

	def gather(self, mesh:bpy.types.Mesh, shapekey_name:str) -> np.ndarray:
		attr = self.validate(mesh, shapekey_name, remove_invalid=True, create_if_invalid=True)
		if not attr:
			print(f"Attribute {self.name_fn(shapekey_name)} not found or invalid.")
			return
		
		data_size = None
		np_type = None
		data_entry = None

		if _prop := _data_type_element_prop_[self.type]:
			data_size, np_type, data_entry = _prop
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented data type {self.type}")

		if self.domain == "CORNER":
			data = np.empty(len(mesh.loops) * data_size, dtype = np_type)
			attr.data.foreach_get(data_entry, data)
		elif self.domain == "POINT":
			data = np.empty(len(mesh.vertices) * data_size, dtype = np_type)
			attr.data.foreach_get(data_entry, data)
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented domain {self.domain}")

		return data

	def set_data(self, mesh:bpy.types.Mesh, shapekey_name:str, data:np.ndarray, create_if_not_exist = True) -> bool:
		attr = self.validate(mesh, shapekey_name, remove_invalid=True, create_if_invalid=create_if_not_exist)
		if not attr:
			print(f"Attribute {self.name_fn(shapekey_name)} not found or invalid.")
			return False

		data_size = None
		np_type = None
		data_entry = None

		if _prop := _data_type_element_prop_[self.type]:
			data_size, np_type, data_entry = _prop
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented data type {self.type}")

		if self.domain == "CORNER":
			attr.data.foreach_set(data_entry, data)
		elif self.domain == "POINT":
			attr.data.foreach_set(data_entry, data)
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented domain {self.domain}")
		
		return True

_morph_attr_factory_list_ = {
	"morph_normals": MorphAttrFactory("NRM", "CORNER", "FLOAT_VECTOR"),
	"morph_target_colors": MorphAttrFactory("COL", "CORNER", "FLOAT_COLOR"),
}

def MorphNormals():
	return _morph_attr_factory_list_["morph_normals"]

def MorphTargetColors():
	return _morph_attr_factory_list_["morph_target_colors"]

def MorphAttr(name:str):
	return _morph_attr_factory_list_[name]

def addShapeKeyAttributes(obj:bpy.types.Object, shapekey_name:str, replace=False):
	mesh = obj.data
	for factory in _morph_attr_factory_list_.values():
		factory.create(mesh, shapekey_name, replace)

def morphPanelRecalculateActiveNormals(obj):

	active = obj.data.shape_keys.key_blocks[obj.active_shape_key_index]
	morph_name = active.name
	mesh = obj.data

	if f"NRM_{morph_name}" not in mesh.attributes:
		mesh.attributes.new(name=f"NRM_{morph_name}", type="FLOAT_VECTOR", domain="POINT")

	if f"TAN_{morph_name}" not in mesh.attributes:
		mesh.attributes.new(name=f"TAN_{morph_name}", type="FLOAT_VECTOR", domain="POINT")

	nrm_attr = mesh.attributes.get(f"NRM_{morph_name}")
	tan_attr = mesh.attributes.get(f"TAN_{morph_name}")

	obj.data.calc_normals_split()
	obj.data.calc_tangents()

	vid_lid_list = [0 for _ in range(len(obj.data.vertices))]
	temp_sk_normals = active.normals_vertex_get()
	sk_normals_lists = [temp_sk_normals[i:i+3] for i in range(0, len(temp_sk_normals), 3)]

	basis_normals, basis_tangents, basis_tangentsigns = GetNormalTangents(obj.data, True, True, vid_lid_list)

	for face in obj.data.polygons:
		for l_id in face.loop_indices:
			vid_lid_list[obj.data.loops[l_id].vertex_index] = l_id

	sk_tangents = [utils_math.GramSchmidtOrthogonalize(np.array(mesh.loops[loop_idx].tangent), mathutils.Vector(n)) for loop_idx, n in zip(vid_lid_list, sk_normals_lists)]

	for i in range(len(mesh.vertices)):
		sk_nrm = mathutils.Vector(sk_normals_lists[i]).normalized()
		obj_nrm = mathutils.Vector((n for n in basis_normals[i])).normalized()
		dot_product = obj_nrm.dot(sk_nrm)

		nrm_attr.data[i].vector = sk_nrm - (obj_nrm * dot_product)
		tan_attr.data[i].vector = basis_tangentsigns[i] * (sk_tangents[i] - basis_tangents[i])