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
			print(f"Shapekey name {shapekey_name} invalid.")
			return
		
		self.from_mesh_data_fn(attr, shapekey_name, mesh)

	def to_mesh_data(self, attr, mesh:bpy.types.Mesh, shapekey_name:str) -> None:
		attr = self.validate(mesh, shapekey_name, remove_invalid=True, create_if_invalid=True)
		if not attr:
			print(f"Shapekey name {shapekey_name} invalid.")
			return
		
		self.to_mesh_data_fn(attr, shapekey_name, mesh)

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
		'''
		Set the data of the attribute. If the attribute does not exist, create it if create_if_not_exist is True

		:param mesh: bpy.types.Mesh
		:param shapekey_name: str
		:param data: np.ndarray. Data must be a num_elem * data_size matrix
		:param create_if_not_exist: bool. If True, create the attribute if it does not exist
		'''
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
			attr.data.foreach_set(data_entry, data.ravel())
		elif self.domain == "POINT":
			attr.data.foreach_set(data_entry, data.ravel())
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented domain {self.domain}")
		
		return True

	def set_data_foreach(self, mesh:bpy.types.Mesh, shapekey_name:str, data:np.ndarray, create_if_not_exist = True) -> bool:
		'''
		Set all elements with the same data. If the attribute does not exist, create it if create_if_not_exist is True

		:param mesh: bpy.types.Mesh
		:param shapekey_name: str
		:param data: np.ndarray. Data must be a (data_size, 1) vector or equivalent size
		:param create_if_not_exist: bool. If True, create the attribute if it does not exist		
		'''
		attr = self.validate(mesh, shapekey_name, remove_invalid=True, create_if_invalid=create_if_not_exist)
		if not attr:
			print(f"Attribute {self.name_fn(shapekey_name)} not found or invalid.")
			return False
		
		num_elements = None
		data_size = None
		np_type = None
		data_entry = None
		
		if _prop := _data_type_element_prop_[self.type]:
			data_size, np_type, data_entry = _prop
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented data type {self.type}")
		
		assert len(data.ravel()) == data_size, f"Data size mismatch. Expected {data_size}, got {len(data.ravel())}"

		if self.domain == "CORNER":
			num_elements = len(mesh.loops)
		elif self.domain == "POINT":
			num_elements = len(mesh.vertices)
		else:
			raise ValueError(f"MorphAttrFactory.gather(): Unimplemented domain {self.domain}")

		populated_data = np.tile(data, (num_elements, 1))

		return self.set_data(mesh, shapekey_name, populated_data, create_if_not_exist)


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
