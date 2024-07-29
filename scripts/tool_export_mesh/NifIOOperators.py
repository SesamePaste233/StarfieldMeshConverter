import bpy

import NifIO

import nif_armature

import re
import os

import utils_blender

from bpy_extras.io_utils import ImportHelper
from utils_material import is_mat

import utils_common as utils

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
		layout.label(text="Assets Folder:")
		layout.prop(context.scene, "assets_folder", text="")
		
		layout.label(text="Import Options:")
		layout.prop(self, "skeleton_name")
		layout.prop(self, "max_lod")
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
		if is_mat(mat):
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
	max_border: bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 otherwise.",
		default=0,
	)
	WEIGHTS: bpy.props.BoolProperty(
		name="Weights",
		description="Export vertex weights, only work with valid armature modifiers attached to objects.",
		default=True
	)

	use_secondary_uv: bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
	)

	export_morph = False #: bpy.props.BoolProperty(
#		name="Export morph data (if any)",
#		description="Export shape keys as morph keys",
#		default=False,
#	)

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
		layout.prop(self, "max_border")

		layout.label(text="Export Datatypes:") 
		# Create a checkbox for each item
		layout.prop(self, "WEIGHTS")
		layout.prop(self, "use_secondary_uv")
		
		# Draw a horizontal line
		layout.separator()
		layout.label(text="Additional Data:") 
		#layout.prop(self, "export_morph", text="Morph Data")
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

__classes__ = [
	SGB_UL_FileListItems,
	ImportNifFileList,
	ImportCustomNif,
    ExportCustomNif,
]

def register():
    for cls in __classes__:
        bpy.utils.register_class(cls)
	
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import_nif)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export_nif)
		
def unregister():
    for cls in __classes__:
        bpy.utils.unregister_class(cls)
		
    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_nif)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_nif)