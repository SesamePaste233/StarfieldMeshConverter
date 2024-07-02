import bpy
import os
import sys
from numpy.linalg import LinAlgError

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

import utils_blender

import utils_common as utils

import MeshIO

import MorphIO

import NifIO

import nif_armature

import PhysicsPanel as PhysicsPanel

import MaterialPanel as MaterialPanel

import ImportSkeleOp as ImportSkeleOp

import Preferences as Preferences

import utils_transfer as transfer

#import imp
#imp.reload(utils_blender)
#imp.reload(utils)
#imp.reload(MeshIO)
#imp.reload(MorphIO)
#imp.reload(NifIO)
#imp.reload(nif_armature)

bl_info = {
	"name": "Starfield Geometry Bridge",
	"author": "SesamePaste",
	"version": (1, 0, 0),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Export .mesh geometry file for starfield.",
	"warning": "",
	"category": "Import-Export",
	}

# Define a list of items with labels
export_items = [
	("GEO", "Geometry", "Export geometry data (positions and indices)."),
	("NORM", "Normals", "Export normals data."),
	("VERTCOLOR", "Vertex Color", "Export vertex color data."),
	("WEIGHTS", "Weights", "Export vertex groups data."),
]

# Export operator
class ExportCustomMesh(bpy.types.Operator):
	bl_idname = "export_scene.custom_mesh"
	bl_label = "Export Custom Mesh"
	
	filepath: bpy.props.StringProperty(options={'HIDDEN'})
	filename: bpy.props.StringProperty(default='untitled.mesh')
	filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})

	mesh_scale: bpy.props.FloatProperty(
		name="Scale",
		default=1,
	)
	max_border: bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 otherwise.",
		default=0,
	)
	use_world_origin: bpy.props.BoolProperty(
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	)
	normalize_weights: bpy.props.BoolProperty(
		name="Normalize weights",
		description="",
		default=True,
	)
	GEO: bpy.props.BoolProperty(
		name="Geometry",
		description=export_items[0][2],
		default=True
	)
	NORM: bpy.props.BoolProperty(
		name="Normals",
		description=export_items[1][2],
		default=True
	)
	VERTCOLOR: bpy.props.BoolProperty(
		name="Vertex Color",
		description=export_items[2][2],
		default=True
	)
	WEIGHTS: bpy.props.BoolProperty(
		name="Weights",
		description=export_items[3][2],
		default=True
	)
	export_morph: bpy.props.BoolProperty(
		name="Export morph data (if any)",
		description="Export shape keys as morph keys",
		default=False,
	)

	export_sf_mesh_open_folder: bpy.props.BoolProperty(
		name="Open folder after export",
		default=False,
	)
	export_sf_mesh_hash_result: bpy.props.BoolProperty(
		name="Generate hash names",
		description="Export into [hex1]\\[hex2].mesh instead of [name].mesh",
		default=False,
	)

	def execute(self,context):
		original_active = utils_blender.GetActiveObject()
		original_selected = utils_blender.GetSelectedObjs(True)
		mesh_success, _, _, _ = MeshIO.ExportMesh(self,context,self.filepath,self)

		if 'FINISHED' in mesh_success and self.export_morph:
			utils_blender.SetSelectObjects(original_selected)
			utils_blender.SetActiveObject(original_active)
			_file_name, _ =os.path.splitext(self.filepath)
			morph_success, _ = MorphIO.ExportMorph(self,context, _file_name + ".dat", self)
			if 'FINISHED' in morph_success:
				self.report({'INFO'}, "Operation successful.")

			return morph_success
		
		return mesh_success

	def invoke(self, context, event):
		_obj = context.active_object
		if _obj:
			self.filename = utils.sanitize_filename(_obj.name) + '.mesh'
		else:
			self.filename = 'untitled.mesh'

		if os.path.isdir(os.path.dirname(self.filepath)):
			self.filepath = os.path.join(os.path.dirname(self.filepath),self.filename)

		self.mesh_scale = context.scene.mesh_scale
		self.max_border = context.scene.max_border
		self.use_world_origin = context.scene.use_world_origin
		self.normalize_weights = context.scene.normalize_weights
		self.GEO = context.scene.GEO
		self.NORM = context.scene.NORM
		self.VERTCOLOR = context.scene.VERTCOLOR
		self.WEIGHTS = context.scene.WEIGHTS
		self.export_sf_mesh_open_folder = context.scene.export_sf_mesh_open_folder
		self.export_sf_mesh_hash_result = context.scene.export_sf_mesh_hash_result
		self.export_morph = context.scene.export_morph

		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

# Import operator
class ImportCustomMesh(bpy.types.Operator):
	bl_idname = "import_scene.custom_mesh"
	bl_label = "Import Custom Mesh"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='untitled.mesh')
	
	filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})

	import_as_read_only: bpy.props.BoolProperty(
		name="As Read Only",
		description="The object will be marked as read only. You can import morph once, however, as long as there's morph data in this object, any attempt to import a new morph will be prohibited.",
		default=False
	)
	meshlets_debug: bpy.props.BoolProperty(
		name="Debug Meshlets",
		description="Debug option. DO NOT USE.",
		default=False
	)
	culldata_debug: bpy.props.BoolProperty(
		name="Debug CullData",
		description="Debug option. DO NOT USE.",
		default=False
	)
	tangents_debug: bpy.props.BoolProperty(
		name="Debug Tangent Vectors",
		description="Debug option. DO NOT USE.",
		default=False
	)

	def execute(self, context):
		return MeshIO.ImportMesh(self.filepath, self, context, self)

	def invoke(self, context, event):
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ImportCustomNif(bpy.types.Operator):
	bl_idname = "import_scene.custom_nif"
	bl_label = "Import Custom Nif"
	
	def get_skeleton_names(self, context):
		nif_armature.LoadAllSkeletonLookup()
		skel_names = nif_armature.GetAvailableSkeletonNames()
		items = [(' ', 'CHOOSE YOUR SKELETON', 'Auto match skeleton.')]
		for name in skel_names:
			items.append((name, name, name))
		return tuple(items)

	filter_glob: bpy.props.StringProperty(default="*.nif", options={'HIDDEN'})

	assets_folder: bpy.props.StringProperty(subtype="FILE_PATH")

	debug_havok_physics: bpy.props.BoolProperty(
		name="Visualize Havok Cloth Sim Data",
		description="Reinterpret Havok Cloth Sim Data as mesh objects and capsules.",
		default=False
	)

	import_as_read_only: bpy.props.BoolProperty(
		name="As Read Only",
		description="The object will be marked as read only. You can import morph once, however, as long as there's morph data in this object, any attempt to import a new morph will be prohibited.",
		default=False
	)
	correct_rotation: bpy.props.BoolProperty(
		name="Correct Rotation",
		description="Correct Beth's weird rotations and translations. Makes the model consistent with the skeleton.",
		default=True
	)
	max_lod: bpy.props.IntProperty(
		name="Max Lod",
		description="Maximum Loaded LoD, 0 for loading all LoDs.",
		default=1,
	)
	skeleton_name: bpy.props.EnumProperty(
		name="Skeleton Template",
		description="",
		items=get_skeleton_names,
		default=0,
	)
	boneinfo_debug: bpy.props.BoolProperty(
		name="Debug BoneInfo",
		description="Debug option. DO NOT USE.",
		default=False
	)
	meshlets_debug: bpy.props.BoolProperty(
		name="Debug Meshlets",
		description="Debug option. DO NOT USE.",
		default=False
	)
	culldata_debug: bpy.props.BoolProperty(
		name="Debug CullData",
		description="Debug option. DO NOT USE.",
		default=False
	)
	tangents_debug: bpy.props.BoolProperty(
		name="Debug Tangent Vectors",
		description="Debug option. DO NOT USE.",
		default=False
	)
	skeleton_register_name: bpy.props.StringProperty(
		name="Register Skeleton As",
		description="Debug option. DO NOT USE.",
		default="",
	)
	geo_bounding_debug: bpy.props.BoolProperty(
		name="Debug Min Max Bounding",
		description="Debug option. DO NOT USE.",
		default=False
	)

	files: bpy.props.CollectionProperty(
        type=bpy.types.OperatorFileListElement,
        options={'HIDDEN', 'SKIP_SAVE'},
    )

	directory: bpy.props.StringProperty(
        subtype='DIR_PATH',
    )

	def execute(self, context):
		skeleton_obj_dict = {}
		for current_file in self.files:
			filepath = os.path.join(self.directory, current_file.name)
			rtn, skel, objs = NifIO.ImportNif(filepath, self, context, self)
			if 'CANCELLED' in rtn:
				self.report({'WARNING'}, f'{current_file} failed to import.')
			elif skel != None and objs != None and len(objs) > 0:
				skeleton_obj_dict[skel] = objs
		
		for skel, objs in skeleton_obj_dict.items():
			prev_coll = bpy.data.collections.new(skel)
			bpy.context.scene.collection.children.link(prev_coll)
			nif_armature.ImportArmatureFromJson(skel, prev_coll, objs, skel)
		return {'FINISHED'}

	def invoke(self, context, event):
		self.assets_folder = context.scene.assets_folder
		self.skeleton_register_name = ""
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

def get_physics_node_tree_names(self, context):
	physics_node_tree_names = [("None", "None", "No physics data.", 'NONE', 0)]
	for node_tree in bpy.data.node_groups:
		if node_tree.bl_idname == 'hclPhysicsTreeType':
			physics_node_tree_names.append((node_tree.name, node_tree.name, node_tree.name, 'NODETREE', len(physics_node_tree_names)))
	return tuple(physics_node_tree_names)

def get_material_names(self, context):
	material_names = []
	for mat in bpy.data.materials:
		if utils.is_mat(mat):
			material_names.append((mat.name, mat.name, mat.name, 'MATERIAL', len(material_names)))

	if len(material_names) == 0:
		material_names = [("None", "None", "No Starfield material data.", 'NONE', 0)]
	return material_names

class ExportCustomNif(bpy.types.Operator):
	bl_idname = "export_scene.custom_nif"
	bl_label = "Export Custom Nif"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='untitled.nif')
	
	filter_glob: bpy.props.StringProperty(default="*.nif", options={'HIDDEN'})

	export_template: bpy.props.EnumProperty(
		name="Nif Template",
		description="",
		items=(('None', "As Is", "Export all items parented to the root node that are interpretable as Nif objects."),
			   ('Auto', "Based On Root Name", "Auto select template based on the name of the root."),),
		default='None',
	)

	mesh_scale: bpy.props.FloatProperty(
		name="Scale",
		default=1,
	)
	max_border: bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 otherwise.",
		default=0,
	)
	normalize_weights: bpy.props.BoolProperty(
		name="Normalize weights",
		description="",
		default=True,
	)
	GEO: bpy.props.BoolProperty(
		name="Geometry",
		description=export_items[0][2],
		default=True
	)
	NORM: bpy.props.BoolProperty(
		name="Normals",
		description=export_items[1][2],
		default=True
	)
	VERTCOLOR: bpy.props.BoolProperty(
		name="Vertex Color",
		description=export_items[2][2],
		default=True
	)
	WEIGHTS: bpy.props.BoolProperty(
		name="Weights",
		description=export_items[3][2],
		default=True
	)
	export_morph: bpy.props.BoolProperty(
		name="Export morph data (if any)",
		description="Export shape keys as morph keys",
		default=False,
	)

	physics_tree: bpy.props.EnumProperty(
		name="Physics Node Tree",
		description="",
		items=get_physics_node_tree_names,
		default=0,
	)

	export_material: bpy.props.BoolProperty(
		name="Export Material",
		description="Export material data to .mat",
		default=False,
	)

	export_sf_mesh_open_folder: bpy.props.BoolProperty(
		name="Open folder after export",
		default=False,
	)
	export_sf_mesh_hash_result: bpy.props.BoolProperty(
		name="Generate hash names",
		description="Export into [hex1]\\[hex2].mesh instead of [name].mesh",
		default=True,
	)

	use_internal_geom_data: bpy.props.BoolProperty(
		name="Use Internal Geometry Data",
		description="Whether to embed geometry data in the nif file. If disabled, models will be saved as external .mesh files.",
		default=True,
	)

	is_head_object: bpy.props.EnumProperty(
		name="Export Head Object",
		description="If the model is a head model with facebones, nif export will export <model_name>.nif and <model_name>_facebones.nif.",	
		items=(('None', "No", "Export the model as-is."),
			   ('Auto', "Auto", "Export model.nif and model_facebones.nif separately if the model has facebone vertex groups."),),
		default='None',
	)


	use_world_origin = False

	def execute(self, context):
		if self.is_head_object == "Auto":
			root = utils_blender.GetActiveObject()
			# Check if the selected object is a mesh
			if root.type == 'MESH':
				# Check if the selected object has 'faceBone_' vertex groups
				facebone_groups = [group for group in root.vertex_groups if group.name.startswith('faceBone_')]

				if len(facebone_groups) > 0:
					rtn = NifIO.ExportNif(self, context, self, replace_facebone_vg_with_head=True)
					if 'FINISHED' in rtn:
						self.report({'INFO'}, "Operation successful.")
						nif_filepath = self.filepath
						export_folder = os.path.dirname(nif_filepath)
						nif_name = os.path.splitext(os.path.basename(nif_filepath))[0]
						facebone_marker = "_facebones"
						self.filepath = os.path.join(export_folder, nif_name + facebone_marker + '.nif')
						return NifIO.ExportNif(self, context, self, replace_facebone_vg_with_head=False)
					else:
						return rtn
				else:
					self.report({'INFO'}, "The selected object does not have facebone vertex groups. Exporting as-is.")
			else:
				self.report({'INFO'}, "The selected object is not a mesh. Selection of the head mesh is required using 'Export Head Object' option.")
				
		return NifIO.ExportNif(self, context, self)

	def invoke(self, context, event):
		_obj = context.active_object
		if _obj:
			self.filename = utils.sanitize_filename(_obj.name) + '.nif'
		else:
			self.filename = 'untitled.nif'

		if os.path.isdir(os.path.dirname(self.filepath)):
			self.filepath = os.path.join(os.path.dirname(self.filepath),self.filename)

		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ImportCustomMorph(bpy.types.Operator):
	bl_idname = "import_scene.custom_morph"
	bl_label = "Import Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})
	as_multiple: bpy.props.BoolProperty(
		name="As Multiple Objs",
		description="Import Morph as multiple objects, allows greater freedom in morph editing.",
		default=False
	)
	morph_panel: bpy.props.BoolProperty(
		name="Use morph panel",
		description="Import to morph panel (next to the shape-keys panel)",
		default=False
	)
	debug_delta_normal: bpy.props.BoolProperty(
		name="Debug Delta Normals",
		description="Debug option. DO NOT USE.",
		default=False
	)
	debug_delta_tangent: bpy.props.BoolProperty(
		name="Debug Delta Tangents",
		description="Debug option. DO NOT USE.",
		default=False
	)
	debug_padding: bpy.props.BoolProperty(
		name="Debug Padding",
		description="Debug option. DO NOT USE.",
		default=False
	)
	def execute(self, context):
		return MorphIO.ImportMorph(self, context, self)

	def invoke(self, context, event):
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ExportCustomMorph(bpy.types.Operator):
	bl_idname = "export_scene.custom_morph"
	bl_label = "Export Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})

	use_world_origin: bpy.props.BoolProperty(
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	)

	def execute(self, context):
		rtn, _ = MorphIO.ExportMorph(self, context, self.filepath, self)
		return rtn

	def invoke(self, context, event):
		self.filename = "morph.dat"

		if os.path.isdir(os.path.dirname(self.filepath)):
			self.filepath = os.path.join(os.path.dirname(self.filepath),self.filename)

		self.use_world_origin = context.scene.use_world_origin
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ExportSFMeshOperator(bpy.types.Operator):
	"""Export the active object"""
	bl_idname = "export_scene.sfmesh"
	bl_label = "Export Active Mesh"

	def execute(self, context):
		_obj = bpy.context.active_object
		if _obj and _obj.type == 'MESH':
			original_active = utils_blender.GetActiveObject()
			original_selected = utils_blender.GetSelectedObjs(True)
			active_object_name = bpy.context.active_object.name
			success,num_verts_in_mesh,_,_ = MeshIO.ExportMesh(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, utils.sanitize_filename(active_object_name) + '.mesh'), self)

			if 'FINISHED' in success and context.scene.export_morph:
				utils_blender.SetSelectObjects(original_selected)
				utils_blender.SetActiveObject(original_active)
				morph_success, num_verts_in_morph = MorphIO.ExportMorph(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, utils.sanitize_filename(active_object_name) + '.dat'), self)
				
				if 'FINISHED' in morph_success:
					if num_verts_in_mesh != num_verts_in_morph:
						self.report({'WARNING'}, "The number of vertices in the mesh and morph data do not match. This may cause issues in the game.")
					else:
						self.report({'INFO'}, "Operation successful.")

				return morph_success
			
			return success
		
		self.report({'WARNING'}, "You didn't choose a object with geometry!")
		return {'CANCELLED'}

class CreateAdvancedMorphEditOperator(bpy.types.Operator):
	bl_idname = "object.advanced_morph_edit_create"
	bl_label = "Advanced Morph Edit"

	def execute(self, context):
		active_obj = utils_blender.GetActiveObject()
		ref_objs = utils_blender.GetSelectedObjs(True)
		if active_obj == None or active_obj.type != 'MESH':
			return {'CANCELLED'}
		
		target_objs = []

		rtn = MorphIO.CreateMorphObjSet(context.scene, context, active_obj, ref_objs, target_objs, self)
		
		return rtn

class SGB_UL_ShapeKeyListItems(bpy.types.UIList):

	def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
		layout.prop(item, "name", text="", emboss=False)
		layout.prop(item, 'enabled', text="")

class shapeKeyList(bpy.types.PropertyGroup):
	name: bpy.props.StringProperty(name="Shape-key name", default="")
	enabled: bpy.props.BoolProperty(default=True)

class TransferShapeKeys(bpy.types.Operator):
	bl_idname = "object.transfer_shape_keys"
	bl_label = "Transfer shape-keys"
	bl_description = "Transfer shape-keys from selected object to active"
	bl_options = {'UNDO'}

	falloff_sigma: bpy.props.FloatProperty(
		name="Falloff Sigma",
		max=1.0,
		min=0.01,
		default=0.15
	)

	copy_range: bpy.props.FloatProperty(
		name="Copy Range",
		max=0.1,
		min=0.001,
		default=0.005
	)

	shape_key_list: bpy.props.CollectionProperty(
        type=shapeKeyList
    )

	shape_key_list_index: bpy.props.IntProperty(
		default=0
	)

	def draw(self, context):
		layout = self.layout

		if context.object == None or len(utils_blender.GetSelectedObjs(True)) == 0:
			self.report({'ERROR'}, "No selected objects found")
			return
		
		layout.label(text=f"From: {context.object.name}")
		layout.label(text=f"To: {[o.name for o in utils_blender.GetSelectedObjs(True)]}")

		row = layout.row(align=True)

		row.prop(self, "falloff_sigma", slider=True)
		row.prop(self, "copy_range", slider=True)

		row = layout.row(align=True)

		layout.template_list(
            "SGB_UL_ShapeKeyListItems",
            "",
            self, "shape_key_list",
            self, "shape_key_list_index",
			type='GRID',
			rows=1,
			columns=4
		)

	def execute(self, context):
		reference = context.object
		target_list = [o for o in utils_blender.GetSelectedObjs(True) if o.type == "MESH"]

		if reference.data.shape_keys == None:
			reference.shape_key_add('Basis')

		transfer_sk = [sk.name for sk in self.shape_key_list if sk.enabled == True]
		
		if len(transfer_sk) == 0:
			self.report({'ERROR'}, "No shape-keys were selected for transfer")
			return {'CANCELLED'}

		bpy.ops.ed.undo_push()

		for target in target_list:
			try:
				transfer.TransferShapekeys(
					reference,
					target,
					transfer_sk,
					falloff_sigma=self.falloff_sigma,
					copy_range=self.copy_range
				)

			except LinAlgError as e:
				self.report({'ERROR'}, "Reference mesh has duplicate vertices.")
				return {'CANCELLED'}
		
		self.report({'INFO'}, f"Transferred {len(transfer_sk)} shape-keys")
		
		return {'FINISHED'}

	def invoke(self, context, event):
		transfer_from = context.object
		target_list = utils_blender.GetSelectedObjs(True)
		self.shape_key_list.clear()

		self.falloff_sigma = 0.15
		self.copy_range = 0.005

		if transfer_from == None or transfer_from.type != "MESH":
			self.report({'ERROR'}, "No active object found")
			return {'CANCELLED'}
		
		elif transfer_from.data.shape_keys == None or len(transfer_from.data.shape_keys.key_blocks) <= 1:
			self.report({'ERROR'}, "No shape-keys found")
			return {'CANCELLED'}
		
		elif len(target_list) == 0:
			self.report({'ERROR'}, "No selected objects found")
			return {'CANCELLED'}

		for sk_name in [sk.name for idx, sk in enumerate(context.object.data.shape_keys.key_blocks) if idx != 0]:
			item = self.shape_key_list.add()
			item.name = sk_name
			item.do_transfer = True
		
		context.window_manager.invoke_props_dialog(self, width=500)
		
		return {'RUNNING_MODAL'}

class ExportSFMeshPanel(bpy.types.Panel):
	"""Panel for the Export Starfield Mesh functionality"""
	bl_idname = "OBJECT_PT_export_sf_mesh"
	bl_label = "Export Starfield Mesh"
	bl_space_type = 'VIEW_3D'
	bl_region_type = 'UI'
	bl_category = 'Tool'

	def draw(self, context):
		layout = self.layout
		# Folder path input
		layout.label(text="Export Folder:")
		layout.prop(context.scene, "export_mesh_folder_path", text="")
		layout.label(text="Assets Folder:")
		layout.prop(context.scene, "assets_folder", text="")

		# Export settings
		layout.label(text="Export Settings:")
		layout.prop(context.scene, "mesh_scale", text="Scale")
		layout.prop(context.scene, "max_border", text="Compression Border")
		layout.prop(context.scene, "use_world_origin", text="Use world origin")
		layout.prop(context.scene, "normalize_weights", text="Normalize weights")
		
		
		layout.label(text="Export Datatypes:") 
		# Create a checkbox for each item
		for item in export_items:
			layout.prop(context.scene, item[0], text=item[1])
		
		layout.prop(context.scene, "export_morph", text="Morph Data")
		   
		layout.label(text="After Export:") 
		layout.prop(context.scene, "export_sf_mesh_open_folder", text="Open export folder")
		layout.prop(context.scene, "export_sf_mesh_hash_result", text="Hash file name")
		# Button to export the selected skeleton
		layout.operator("object.advanced_morph_edit_create", text = "Advanced Morph Edit")
		layout.operator("export_scene.sfmesh", text = "Export .mesh")

		layout.prop(context.scene, "sgb_debug_mode", text="Debug")

class MorphListRecalculateNormals(bpy.types.Operator):
    bl_idname = "object.morph_list_recalculate_normals"
    bl_label = "Recalculate normals"
    bl_description = ""

    def execute(self, context):
        obj = context.object

        bpy.ops.ed.undo_push()

        rtn = utils_blender.morphPanelRecalculateActiveNormals(obj)

        if rtn == False:
            self.report({'ERROR'}, "Shape-key for recalculating normals not found.")
            return {'CANCELLED'}

        self.report({'INFO'}, f"Recalculated normals for {obj.morph_list[obj.morph_list_index].name}")
		
        return {'FINISHED'}

    def invoke(self, context, event):
        return self.execute(context)

class MorphListFromShapeKeys(bpy.types.Operator):
    bl_idname = "object.morph_list_from_shape_keys"
    bl_label = "Create from shape-keys"
    bl_description = ""

    def execute(self, context):
        obj = context.object

        bpy.ops.ed.undo_push()

        if obj.data.shape_keys == None or obj.data.shape_keys != None and len(obj.data.shape_keys.key_blocks) == 1:
            self.report({'ERROR'}, "No shape-keys found")
            return {'CANCELLED'}
        
        morph_names = [morph.name for morph in obj.morph_list]
        shape_key_names = [sk.name for idx, sk in enumerate(obj.data.shape_keys.key_blocks) if idx != 0 and sk.name not in morph_names]
        
        if shape_key_names == []:
            self.report({'ERROR'}, "All shape-keys are already in morph list")
            return {'CANCELLED'}
        
        for sk_name in shape_key_names:
            utils_blender.morphPanelAdd(obj, sk_name)

        return {'FINISHED'}

    def invoke(self, context, event):
        return self.execute(context)

class MorphPanelRemove(bpy.types.Operator):
    bl_idname = "object.morph_panel_remove"
    bl_label = "Remove morph"
    bl_description = "Removes morph from the list and associated object attributes"

    def execute(self, context):
        obj = context.object

        bpy.ops.ed.undo_push()

        morphPanelRemoveActive(obj)

        return {'FINISHED'}

    def invoke(self, context, event):
        return self.execute(context)

class MorphPanelAdd(bpy.types.Operator):
    bl_idname = "object.morph_panel_add"
    bl_label = "Create new"
    bl_description = ""

    def execute(self, context):
        obj = context.object
        items = [item.name for item in context.object.morph_list if item.name.startswith("NewMorph")]

        counter = len(items)

        bpy.ops.ed.undo_push()

        utils_blender.morphPanelAdd(obj, f"NewMorph.{counter}" if counter != 0 else "NewMorph")
        
        return {'FINISHED'}

    def invoke(self, context, event):

        return self.execute(context)

class SGB_PT_Morphs(bpy.types.Panel):
    bl_idname = "SGB_PT_Morphs"

    bl_label = "Starfield Morphs"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = "Item"
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = "data"

    def draw(self, context):
        layout = self.layout
        obj = context.object

        layout.template_list(
            "SGB_UL_MorphPanelList",
            "",
            context.object, "morph_list",
            context.object, "morph_list_index")

        row = layout.row(align=True)
        row.operator("object.morph_panel_add")
        row.operator("object.morph_panel_remove")

        row = layout.row(align=True)
        col = row.column()

        morph_item = obj.morph_list[obj.morph_list_index] if obj.morph_list != -1 and len(obj.morph_list) != obj.morph_list_index else None
        sk = obj.data.shape_keys

        if morph_item != None:
            col.label(text=f"NRM attribute: {'Found' if obj.data.attributes.get(f'NRM_{morph_item.name}') != None else 'Not found'}")
            col.label(text=f"COL attribute: {'Found' if obj.data.attributes.get(f'COL_{morph_item.name}') != None else 'Not found'}")
            col.label(text=f"Shape key: {'Found' if sk != None and sk.key_blocks.find(morph_item.name) != None else 'Not found'}")
            col.operator("object.morph_list_recalculate_normals")

        layout.label(text="Utilities")
        layout.operator("object.morph_list_from_shape_keys")
        layout.operator("object.transfer_shape_keys")

class MorphPanelList(bpy.types.PropertyGroup):
    name: bpy.props.StringProperty(name="Morph name", default="", update=utils_blender.morphPanelUpdateName)
    morph_value: bpy.props.FloatProperty(name="Morph value", max=1.0, min=0.0, update=utils_blender.morphPanelUpdateMorphValue)

class SGB_UL_MorphPanelList(bpy.types.UIList):
    bl_idname = "SGB_UL_MorphPanelList"
    layout_type = "DEFAULT"

    def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
        
        if self.layout_type in {'DEFAULT', 'COMPACT'}:
            layout.scale_x = 1.1
            layout.prop(item, "name", text="", emboss=False)
            layout.separator(factor=-1.0)
            layout.row().prop(item, 'morph_value', text="", slider=True),
            layout.scale_x = 0.7

def morphPanelRemoveActive(obj):
    if obj.morph_list_index == len(obj.morph_list):
        obj.morph_list_index = len(obj.morph_list) - 1

    index = obj.morph_list_index

    if index == -1:
        return

    active = obj.morph_list[index]
    morph_name = active.name
    mesh = obj.data

    if f"NRM_{morph_name}" in mesh.attributes:
        mesh.attributes.remove(mesh.attributes.get(f"NRM_{morph_name}"))

    if f"COL_{morph_name}" in mesh.attributes:
        mesh.attributes.remove(mesh.attributes.get(f"COL_{morph_name}"))

    obj.morph_list.remove(index)

    obj.morph_list_index = index - 1 if index - 1 > -1 else 0

# Add custom menu entries in the File menu
def menu_func_export(self, context):
	self.layout.operator(
		ExportCustomMesh.bl_idname,
		text="Starfield Geometry (.mesh)",
	)

def menu_func_import(self, context):
	self.layout.operator(
		ImportCustomMesh.bl_idname,
		text="Starfield Geometry (.mesh)",
	)

def menu_func_import_morph(self, context):
	self.layout.operator(
		ImportCustomMorph.bl_idname,
		text="Starfield Morph File (.dat)",
	)

def menu_func_export_morph(self, context):
	self.layout.operator(
		ExportCustomMorph.bl_idname,
		text="Starfield Morph File (.dat)",
	)

def menu_func_import_nif(self, context):
	self.layout.operator(
		ImportCustomNif.bl_idname,
		text="Starfield Nif File (.nif)",
	)

def menu_func_export_nif(self, context):
	self.layout.operator(
		ExportCustomNif.bl_idname,
		text="Starfield Nif File (.nif)",
	)

def update_func(self, context):
	utils.export_mesh_folder_path = context.scene.export_mesh_folder_path
	utils.assets_folder = context.scene.assets_folder

	utils.save("cached_paths", 'export_mesh_folder_path', 'assets_folder')

# Register the operators and menu entries
def register():
	utils.load("cached_paths")
	bpy.types.Scene.sgb_debug_mode = bpy.props.BoolProperty(
		name="Debug Mode",
		description="Debug option. DO NOT USE.",
		default=False
	)

	bpy.types.Scene.geometry_bridge_version = bpy.props.StringProperty(
		name="__geometry_bridge_version__",
		default = f"{bl_info['version'][0]}.{bl_info['version'][1]}.{bl_info['version'][2]}",
	)
	bpy.types.Scene.export_mesh_folder_path = bpy.props.StringProperty(
		name="Export Folder",
		subtype='DIR_PATH',
		default= utils.export_mesh_folder_path,
		update = update_func
	)
	bpy.types.Scene.assets_folder = bpy.props.StringProperty(
		name="Assets Folder",
		subtype='DIR_PATH',
		default= utils.assets_folder,
		update = update_func
	)
	bpy.types.Scene.mesh_scale = bpy.props.FloatProperty(
		name="Scale",
		default=1,
	)
	bpy.types.Scene.max_border = bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 (Auto) otherwise.",
		default=0,
	)
	bpy.types.Scene.use_world_origin = bpy.props.BoolProperty(
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	)
	bpy.types.Scene.normalize_weights = bpy.props.BoolProperty(
		name="Normalize weights",
		description="",
		default=False
	)
	bpy.types.Scene.GEO = bpy.props.BoolProperty(
		name="Geometry",
		description=export_items[0][2],
		default=True
	)
	bpy.types.Scene.NORM = bpy.props.BoolProperty(
		name="Normals",
		description=export_items[1][2],
		default=True
	)
	bpy.types.Scene.VERTCOLOR = bpy.props.BoolProperty(
		name="Vertex Color",
		description=export_items[2][2],
		default=True
	)
	bpy.types.Scene.WEIGHTS = bpy.props.BoolProperty(
		name="Weights",
		description=export_items[3][2],
		default=True
	)
	bpy.types.Scene.export_morph = bpy.props.BoolProperty(
		name="Morph Data",
		description="Export shape keys as morph keys",
		default=True
	)
	bpy.types.Scene.export_sf_mesh_open_folder = bpy.props.BoolProperty(
		name="Open folder",
		default=False,
	)
	bpy.types.Scene.export_sf_mesh_hash_result = bpy.props.BoolProperty(
		name="Generate hash names",
		description="Export into [hex1]\\[hex2].mesh instead of [model_name].mesh",
		default=False,
	)

	bpy.utils.register_class(MorphPanelList)

	bpy.types.Object.morph_list = bpy.props.CollectionProperty(
		type=MorphPanelList
	)

	bpy.types.Object.morph_list_index = bpy.props.IntProperty(
		name="Morph list index",
		default=0,
		update=utils_blender.morphPanelUpdateMorphIndex
	)

	bpy.utils.register_class(MorphListFromShapeKeys)
	bpy.utils.register_class(SGB_UL_MorphPanelList)
	bpy.utils.register_class(SGB_PT_Morphs)
	bpy.utils.register_class(MorphPanelAdd)
	bpy.utils.register_class(MorphPanelRemove)
	bpy.utils.register_class(MorphListRecalculateNormals)
	bpy.utils.register_class(ExportCustomMesh)
	bpy.utils.register_class(ImportCustomMesh)
	bpy.utils.register_class(ImportCustomNif)
	bpy.utils.register_class(ImportCustomMorph)
	bpy.utils.register_class(ExportCustomMorph)
	bpy.utils.register_class(ExportSFMeshOperator)
	bpy.utils.register_class(CreateAdvancedMorphEditOperator)
	bpy.utils.register_class(SGB_UL_ShapeKeyListItems)
	bpy.utils.register_class(shapeKeyList)
	bpy.utils.register_class(TransferShapeKeys)
	bpy.utils.register_class(ExportSFMeshPanel)
	bpy.utils.register_class(ExportCustomNif)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import_morph)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import_nif)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export_morph)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export_nif)

	PhysicsPanel.register()
	MaterialPanel.register()
	ImportSkeleOp.register()
	Preferences.register()

def unregister():
	bpy.utils.unregister_class(CreateAdvancedMorphEditOperator)
	bpy.utils.unregister_class(ExportSFMeshOperator)
	bpy.utils.unregister_class(ExportSFMeshPanel)
	bpy.utils.unregister_class(ExportCustomMesh)
	bpy.utils.unregister_class(ImportCustomMesh)
	bpy.utils.unregister_class(ImportCustomNif)
	bpy.utils.unregister_class(ImportCustomMorph)
	bpy.utils.unregister_class(ExportCustomMorph)
	bpy.utils.unregister_class(ExportCustomNif)
	bpy.utils.unregister_class(MorphPanelList)
	bpy.utils.unregister_class(MorphListFromShapeKeys)
	bpy.utils.unregister_class(SGB_UL_MorphPanelList)
	bpy.utils.unregister_class(SGB_PT_Morphs)
	bpy.utils.unregister_class(MorphPanelAdd)
	bpy.utils.unregister_class(MorphPanelRemove)
	bpy.utils.unregister_class(MorphListRecalculateNormals)
	bpy.utils.unregister_class(SGB_UL_ShapeKeyListItems)
	bpy.utils.unregister_class(shapeKeyList)
	bpy.utils.unregister_class(TransferShapeKeys)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_nif)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_morph)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_morph)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_nif)
	del bpy.types.Scene.geometry_bridge_version
	del bpy.types.Scene.export_mesh_folder_path
	del bpy.types.Scene.assets_folder
	del bpy.types.Scene.mesh_scale
	del bpy.types.Scene.max_border
	del bpy.types.Scene.use_world_origin
	del bpy.types.Scene.normalize_weights
	del bpy.types.Scene.GEO
	del bpy.types.Scene.NORM
	del bpy.types.Scene.VERTCOLOR
	del bpy.types.Scene.WEIGHTS
	del bpy.types.Scene.export_sf_mesh_open_folder
	del bpy.types.Scene.export_sf_mesh_hash_result
	del bpy.types.Scene.export_morph

	PhysicsPanel.unregister()
	MaterialPanel.unregister()
	ImportSkeleOp.unregister()
	Preferences.unregister()

if __name__ == "__main__":
	register()