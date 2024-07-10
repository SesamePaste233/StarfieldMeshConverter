import bpy
from bpy_extras.io_utils import ImportHelper
import os
import sys
import re
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

import BoneRegionsPanel as BoneRegionsPanel

#import imp
#imp.reload(utils_blender)
#imp.reload(utils)
#imp.reload(MeshIO)
#imp.reload(MorphIO)
#imp.reload(NifIO)
#imp.reload(nif_armature)

bl_info = {
	"name": "Starfield Geometry Bridge",
	"author": "SesamePaste & Deveris",
	"version": (1, 1, 0),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Export .nif, .dat and .mesh files for Starfield.",
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

	use_secondary_uv: bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
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
		self.use_secondary_uv = context.scene.use_secondary_uv

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


def re_filter_update(self, context):
	self.re_nif_file_list.clear()
	self.re_nif_file_list_index = 0
	self.apply_filter = False

def apply_filter_update(self, context):
	self.re_nif_file_list.clear()
	directory = self.directory
	max_num_scanned_files = self.max_num_scanned_files
	max_num_selected_files = self.max_num_selected_files
	print(directory, self.re_filter, self.negative_re_filter, self.apply_filter)
	if self.apply_filter == True and self.re_filter != "" and directory != "": # Apply regular expression filter
		
		# Get all files under the directory
		try:
			pattern = re.compile(self.re_filter, sum([getattr(re, flag) for flag in self.re_flags]))
		except re.error as e:
			return

		negative_pattern = None
		if self.negative_re_filter != "":
			try:
				negative_pattern = re.compile(self.negative_re_filter, sum([getattr(re, flag) for flag in self.negative_re_flags]))
			except re.error as e:
				negative_pattern = None


		num_scanned_files = 0
		for root, d, f in os.walk(directory):
			for file in f:
				if not file.endswith('.nif'):
					continue
				if num_scanned_files >= max_num_scanned_files:
					break
				if pattern.match(file) is not None:
					if negative_pattern != None and negative_pattern.match(file) is not None:
						continue
					nif_path = os.path.join(root, file)
					nif_file = self.re_nif_file_list.add()
					nif_file.path = nif_path
					nif_file.nif_name = os.path.splitext(file)[0]
					nif_file.enabled = True
				if len(self.re_nif_file_list) >= max_num_selected_files:
					break
				num_scanned_files += 1
			
			if num_scanned_files >= max_num_scanned_files:
				print('WARNING', f"Scanned {max_num_scanned_files} files. The current directory has too many files!")
				break
			if len(self.re_nif_file_list) >= max_num_selected_files:
				print('WARNING', f"Selected {max_num_selected_files} files. Please refine your regular expression filter.")
				break

		print('INFO', f"Scanned {num_scanned_files} files. Selected {len(self.re_nif_file_list)} files.")

class SGB_UL_FileListItems(bpy.types.UIList):
	def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
		row = layout.row()
		row.prop(item, "nif_name", text="", emboss=False)
		row.prop(item, 'enabled', text="")

class ImportNifFileList(bpy.types.PropertyGroup):
	path: bpy.props.StringProperty(name="Nif Path", default="")
	nif_name: bpy.props.StringProperty(name="Nif Name", default="")
	enabled: bpy.props.BoolProperty(default=True)

class ImportCustomNif(bpy.types.Operator, ImportHelper):
	bl_idname = "import_scene.custom_nif"
	bl_label = "Import Custom Nif"
	
	filename_ext = "."
	use_filter_folder = True

	def get_skeleton_names(default_display_value="None", default_display_name="None"):
		def get_skeleton_names_impl(self, context):
			nif_armature.LoadAllSkeletonLookup()
			skel_names = nif_armature.GetAvailableSkeletonNames()
			items = [(' ', default_display_value, default_display_name)]
			for name in skel_names:
				items.append((name, name, name))
			return tuple(items)
		return get_skeleton_names_impl
	
	filter_glob: bpy.props.StringProperty(default="*.nif;*.niflst", options={'HIDDEN'})

	assets_folder: bpy.props.StringProperty(subtype="FILE_PATH")

	debug_havok_physics: bpy.props.BoolProperty(
		name="Debug Havok Cloth Sim Data",
		description="Reinterpret Havok Cloth Sim Data as mesh objects and capsules. (Requires Load Havok Skeleton)",
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
		items=get_skeleton_names("CHOOSE YOUR SKELETON", "Auto match skeleton in database"),
		default=0,
	)
	load_havok_skeleten: bpy.props.BoolProperty(
		name="Load Havok Skeleton (if any)",
		description="Load Havok Skeleton (if any)",
		default=True
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
	skeleton_register_name_overwrite: bpy.props.EnumProperty(
		name="Register Skeleton As",
		description="Debug option. DO NOT USE.",
		items=get_skeleton_names("None", "Do not overwrite registered skeleton."),
		default=0,
	)
	skeleton_register_overwrite: bpy.props.BoolProperty(
		name="Overwrite Existing Skeleton",
		description="Debug option. DO NOT USE.",
		default=True
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

	re_filter: bpy.props.StringProperty(
		name="Regular Expression Filter",
		description="Apply a regular expression filter to the files under current directory.",
		default="",
		update=re_filter_update
	)

	negative_re_filter: bpy.props.StringProperty(
		name="Negative Regular Expression Filter",
		description="Apply a negative regular expression filter to the files under current directory.",
		default="",
		update=re_filter_update
	)

	re_flags: bpy.props.EnumProperty(
		name="Regular Expression Flags",
		description="Regular Expression Flags",
		items=(
			('IGNORECASE', "Ignore Case", "Ignore case."),
			('MULTILINE', "Multiline", "Multiline."),
			('DOTALL', "Dot All", "Dot All."),
			('VERBOSE', "Verbose", "Verbose."),
			('UNICODE', "Unicode", "Unicode."),
			('LOCALE', "Locale", "Locale."),
			('ASCII', "ASCII", "ASCII."),
		),
		default=set(),
		options={'ENUM_FLAG'}
	)

	negative_re_flags: bpy.props.EnumProperty(
		name="Negative Regular Expression Flags",
		description="Negative Regular Expression Flags",
		items=(
			('IGNORECASE', "Ignore Case", "Ignore case."),
			('MULTILINE', "Multiline", "Multiline."),
			('DOTALL', "Dot All", "Dot All."),
			('VERBOSE', "Verbose", "Verbose."),
			('UNICODE', "Unicode", "Unicode."),
			('LOCALE', "Locale", "Locale."),
			('ASCII', "ASCII", "ASCII."),
		),
		default=set(),
		options={'ENUM_FLAG'}
	)

	apply_filter: bpy.props.BoolProperty(
		name="Apply Regular Expression",
		description="Apply RE and Show the files that match the regular expression filter.",
		default=False,
		update=apply_filter_update
	)

	re_nif_file_list: bpy.props.CollectionProperty(
        type=ImportNifFileList
    )

	re_nif_file_list_index: bpy.props.IntProperty(
		default=0
	)

	max_num_scanned_files:bpy.props.IntProperty(
		default=10000
	)

	max_num_selected_files:bpy.props.IntProperty(
		default=64
	)

	def FAKE_BUTTON_generate_re_filtered_files_txt_update(self, context):
		if self.FAKE_BUTTON_generate_re_filtered_files_txt == True:
			if len(self.re_nif_file_list) == 0:
				self.FAKE_BUTTON_generate_re_filtered_files_txt = False
				return
			
			txt_file_path = os.path.join(self.directory, "filtered_nif_files.niflst")
			with open(txt_file_path, 'w') as f:
				for file in self.re_nif_file_list:
					if file.enabled == True:
						f.write(file.path + '\n')

			def draw(self, context):
				self.layout.label(text="Refresh file list")
				self.layout.label(text=f"Saved filtered nif files list to {txt_file_path}")

			bpy.context.window_manager.popup_menu(draw, title = "Saved!", icon = 'INFO')

			self.FAKE_BUTTON_generate_re_filtered_files_txt = False

	FAKE_BUTTON_generate_re_filtered_files_txt: bpy.props.BoolProperty(
		name="Generate Filtered Files List",
		description="Generate a txt file that contains the filtered nif files.",
		default=False,
		update=FAKE_BUTTON_generate_re_filtered_files_txt_update
	)

	def draw(self, context):
		layout = self.layout
		layout.prop(self, "assets_folder")
		layout.prop(self, "skeleton_name")
		layout.prop(self, "correct_rotation")
		layout.prop(self, "max_lod")
		layout.prop(self, "import_as_read_only")
		layout.prop(self, "load_havok_skeleten")

		layout.label(text="Register Skeleton To Database:")
		if self.skeleton_register_overwrite:
			layout.prop(self, "skeleton_register_name_overwrite")
		else:
			layout.prop(self, "skeleton_register_name")
		layout.prop(self, "skeleton_register_overwrite")

		layout.label(text="Debug Options:")
		layout.prop(self, "debug_havok_physics")
		layout.prop(self, "boneinfo_debug")
		layout.prop(self, "meshlets_debug")
		layout.prop(self, "culldata_debug")
		layout.prop(self, "tangents_debug")
		layout.prop(self, "geo_bounding_debug")

		layout.label(text="Batch Import:")
		layout.prop(self, "re_filter")
		layout.prop(self, "re_flags")

		layout.prop(self, "negative_re_filter")
		layout.prop(self, "negative_re_flags")

		layout.prop(self, "max_num_scanned_files", text="Max Scanned Files")
		layout.prop(self, "max_num_selected_files", text="Max Selected Files")

		row = layout.row(align=True)
		row.prop(self, "apply_filter", text=f"Apply Filter (Count: {len(self.re_nif_file_list)})")
		col = layout.column(align=True)
		col.enabled = self.apply_filter
		col.template_list(
			listtype_name="SGB_UL_FileListItems",
			list_id="", 
			dataptr=self, 
			propname="re_nif_file_list", 
			active_dataptr=self, 
			active_propname="re_nif_file_list_index", 
			rows=5
		)
		row.prop(self, "FAKE_BUTTON_generate_re_filtered_files_txt", text="Save List", icon='TEXT')

	def execute(self, context):
		if self.apply_filter == True:
			files = [file.path for file in self.re_nif_file_list if file.enabled == True]
			self.apply_filter = False
		else:
			files = [os.path.join(self.directory, file.name) for file in self.files]

		# If file ends with .txt, it's a list of nif files
		for current_file in files:
			if current_file.endswith('.niflst'):
				with open(current_file, 'r') as f:
					for line in f.readlines():
						txt_file_path = line.strip()
						# Check if the file exists and is a nif file
						if txt_file_path.endswith('.nif') and os.path.exists(txt_file_path):
							files.append(txt_file_path)

		skeleton_obj_dict = {}
		for current_file in files:
			filepath = current_file
			rtn, skel, objs = NifIO.ImportNif(filepath, self, context, self)
			if 'CANCELLED' in rtn:
				self.report({'WARNING'}, f'{os.path.basename(current_file)} failed to import.')
			elif skel != None and objs != None and len(objs) > 0:
				if skel in skeleton_obj_dict:
					skeleton_obj_dict[skel] += objs
				else:
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

	use_secondary_uv: bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
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

	additive_export: bpy.props.EnumProperty(
		name="Base Nif from",
		description="Modify only the BSGeometry nodes in imported nif if the selected ExportScene node is from nif import. May raise errors if the number and names of models don't match.",
		items=(('None', "Disable", "Export the model as-is."),
			   ('Selected', "Selected", "Overwrite selected file if applicable."),
			   ('Root', "Root", "Overwrite nif file from Import_Nif_Path property of the root node."),
			   ),
		default='None',
	)

	overwrite_material_paths: bpy.props.BoolProperty(
		name="Overwrite Material Paths",
		description="Overwrite the material paths during additive export.",
		default=False,
	)

	use_world_origin = False

	def draw(self, context):
		layout = self.layout
		layout.prop(self, "export_template")
		layout.prop(self, "mesh_scale")
		layout.prop(self, "max_border")
		layout.prop(self, "normalize_weights")

		layout.label(text="Export Datatypes:") 
		# Create a checkbox for each item
		for item in export_items:
			layout.prop(self, item[0], text=item[1])

		layout.prop(self, "use_secondary_uv")
		
		# Draw a horizontal line
		layout.separator()
		layout.label(text="Additional Data:") 
		layout.prop(self, "export_morph", text="Morph Data")
		layout.prop(self, "physics_tree")
		layout.prop(self, "export_material")
		
		layout.separator()
		layout.label(text="Special Controls:") 
		layout.prop(self, "use_internal_geom_data")
		layout.prop(self, "is_head_object")
		layout.prop(self, "export_sf_mesh_hash_result")

		layout.separator()
		layout.label(text="Additive Export:") 
		layout.prop(self, "additive_export")
		layout.prop(self, "overwrite_material_paths")

		layout.separator()
		layout.label(text="After Export:") 
		layout.prop(self, "export_sf_mesh_open_folder")

	def execute(self, context):
		if self.is_head_object == "Auto":
			root = utils_blender.GetActiveObject()
			if not root:
				self.report({'ERROR'}, "No object selected.")
				return {'CANCELLED'}
			# Check if the selected object is a mesh
			if root.type == 'MESH':
				# Check if the selected object has 'faceBone_' vertex groups
				facebone_groups = [group for group in root.vertex_groups if group.name.startswith('faceBone_')]

				if len(facebone_groups) > 0:
					rtn = NifIO.ExportNif(self, context, self, head_object_mode='Base')
					if 'FINISHED' in rtn:
						self.report({'INFO'}, "Operation successful.")
						nif_filepath = self.filepath
						export_folder = os.path.dirname(nif_filepath)
						nif_name = os.path.splitext(os.path.basename(nif_filepath))[0]
						facebone_marker = "_facebones"
						self.filepath = os.path.join(export_folder, nif_name + facebone_marker + '.nif')
						return NifIO.ExportNif(self, context, self, head_object_mode='FaceBone')
					else:
						return rtn
				else:
					self.report({'INFO'}, "The selected object does not have facebone vertex groups. Exporting as-is.")
					return NifIO.ExportNif(self, context, self)
			else:
				self.report({'INFO'}, "The selected object is not a mesh. Selection of the head mesh is required using 'Export Head Object' option.")
				return NifIO.ExportNif(self, context, self)
		else:
			selected_objects = utils_blender.GetSelectedObjs(False)
			if len(selected_objects) == 0:
				self.report({'ERROR'}, "No object selected.")
				return {'CANCELLED'}
			
			if len(selected_objects) < 2 or not all([obj.type == 'EMPTY' for obj in selected_objects]):
				return NifIO.ExportNif(self, context, self)
			
			for obj in selected_objects:
				utils_blender.SetActiveObject(obj)
				export_file_name = obj.name
				if obj.get('Import_Nif_Path') == None:
					export_file_name = os.path.basename(obj['Import_Nif_Path'])
				elif obj.users_collection and len(obj.users_collection) > 0:
					coll = obj.users_collection[0]
					export_file_name = coll.name
				
				if not export_file_name.endswith('.nif'):
					export_file_name += '.nif'

				self.filepath = os.path.join(os.path.dirname(self.filepath), export_file_name)
				self.use_secondary_uv = True

				rtn = NifIO.ExportNif(self, context, self)
				if 'CANCELLED' in rtn:
					self.report({'WARNING'}, f"Failed to export {obj.name}.")
					continue
			
		return {'FINISHED'}

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
	use_attributes: bpy.props.BoolProperty(
		name="Import attributes",
		description="Import normals, tangents and colors as attributes.",
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
	bl_description = "Transfer shape-keys from active object to selected"
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
		import utils_transfer as transfer
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
    bl_label = "Recalculate Normals"
    bl_description = "Recalculate normals and tangents deltas for this shape-key."
	
    @classmethod
    def poll(cls, context):
        return True
	
    def execute(self, context):
        obj = context.object

        bpy.ops.ed.undo_push()

        rtn = utils_blender.morphPanelRecalculateActiveNormals(obj)

        if rtn == False:
            self.report({'ERROR'}, "Shape-key for recalculating normals not found.")
            return {'CANCELLED'}

        self.report({'INFO'}, f"Recalculated normals for {obj.data.shape_keys.key_blocks[obj.active_shape_key_index].name}")
		
        return {'FINISHED'}

    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)

def menu_func_morphs(self, context):
	layout = self.layout
	layout.separator()

	col = layout.column()

	obj = context.object

	if obj.data.shape_keys == None or len(obj.data.shape_keys.key_blocks) == 0:
		return
	
	if obj.active_shape_key_index == 0:
		return

	sk = obj.data.shape_keys.key_blocks[obj.active_shape_key_index]
	col.label(text="Attributes")

	row = layout.row(align=True)
	row.label(text=f"NRM: {'Found' if obj.data.attributes.get(f'NRM_{sk.name}') != None else 'Not found'}")
	row.label(text=f"TAN: {'Found' if obj.data.attributes.get(f'TAN_{sk.name}') != None else 'Not found'}")
	row.label(text=f"COL: {'Found' if obj.data.attributes.get(f'COL_{sk.name}') != None else 'Not found'}")
	
	row = layout.row(align=True)
	#row.operator("object.morph_list_recalculate_normals")
	row.operator(TransferShapeKeys.bl_idname)

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
	bpy.types.Scene.use_secondary_uv = bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
	)

	bpy.utils.register_class(SGB_UL_FileListItems)
	bpy.utils.register_class(ImportNifFileList)

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
	#bpy.utils.register_class(ExportSFMeshPanel)
	bpy.utils.register_class(ExportCustomNif)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import_morph)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import_nif)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export_morph)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export_nif)
	bpy.types.DATA_PT_shape_keys.append(menu_func_morphs)

	PhysicsPanel.register()
	MaterialPanel.register()
	ImportSkeleOp.register()
	Preferences.register()
	BoneRegionsPanel.register()

def unregister():
	bpy.utils.unregister_class(CreateAdvancedMorphEditOperator)
	bpy.utils.unregister_class(ExportSFMeshOperator)
	#bpy.utils.unregister_class(ExportSFMeshPanel)
	bpy.utils.unregister_class(ExportCustomMesh)
	bpy.utils.unregister_class(ImportCustomMesh)
	bpy.utils.unregister_class(ImportCustomNif)
	bpy.utils.unregister_class(ImportCustomMorph)
	bpy.utils.unregister_class(ExportCustomMorph)
	bpy.utils.unregister_class(ExportCustomNif)
	bpy.utils.unregister_class(MorphListRecalculateNormals)
	bpy.utils.unregister_class(SGB_UL_ShapeKeyListItems)
	bpy.utils.unregister_class(shapeKeyList)
	bpy.utils.unregister_class(TransferShapeKeys)
	bpy.utils.unregister_class(SGB_UL_FileListItems)
	bpy.utils.unregister_class(ImportNifFileList)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_nif)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_morph)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_morph)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_nif)
	bpy.types.DATA_PT_shape_keys.remove(menu_func_morphs)
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
	del bpy.types.Scene.use_secondary_uv

	PhysicsPanel.unregister()
	MaterialPanel.unregister()
	ImportSkeleOp.unregister()
	Preferences.unregister()
	BoneRegionsPanel.unregister()

if __name__ == "__main__":
	register()