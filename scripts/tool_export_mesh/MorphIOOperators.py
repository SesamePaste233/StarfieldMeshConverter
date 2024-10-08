import bpy

import MorphIO

import os

import utils_common as utils

import utils_blender	

class ImportCustomMorph(bpy.types.Operator):
	bl_idname = "import_scene.custom_morph"
	bl_label = "Import Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})
	use_colors: bpy.props.BoolProperty(
		name="Import colors",
		description="Import colors as attributes.",
		default=False
	)

	use_normals: bpy.props.BoolProperty(
		name="Import normals",
		description="Import normals as attributes.",
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
	
	def execute(self, context):
		return MorphIO.ImportMorphFromNumpy(self.filepath, self, self.debug_delta_normal, use_colors=self.use_colors, use_normals=self.use_normals)

	def invoke(self, context, event):
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ExportCustomMorph(bpy.types.Operator):
	bl_idname = "export_scene.custom_morph"
	bl_label = "Export Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})

	use_world_origin = True

	use_secondary_uv: bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
	)

	snapping_enabled: bpy.props.BoolProperty(
		name="Snap Morph Data To Selected",
		description="Snapping morph data of connecting vertices to closest verts from selected objects.",
		default=False,
	)

	snap_lerp_coeff: bpy.props.FloatProperty(
		name="Snap Lerp Coefficient",
		description="Lerp coefficient for snapping morph data of connecting vertices to closest verts from selected objects.",
		default=1.0,
		min=0.0,
		max=1.0,
		precision=4,
	)

	snapping_range: bpy.props.FloatProperty(
		name="Snapping Range",
		description="Verts from Active Object will copy morph data from verts from selected objects within Snapping Range.",
		default=0.005,
		min=0.0,
		precision=4,
	)

	snap_delta_positions: bpy.props.BoolProperty(
		name="Snap Delta Positions",
		description="Snapping morph delta positions of connecting vertices to closest verts from selected objects.",
		default=False,
	)

	snap_lerp_coeff_delta_positions: bpy.props.FloatProperty(
		name="Snap Lerp Coefficient Delta Positions",
		description="Lerp coefficient for snapping morph delta positions of connecting vertices to closest verts from selected objects.",
		default=1.0,
		min=0.0,
		max=1.0,
		precision=4,
	)

	def draw(self, context):
		layout = self.layout
		layout.prop(self, "use_secondary_uv")

		report = utils_blender.export_report(report_uv_layers=True)
		box = layout.box()
		if self.use_secondary_uv:
			box.label(text=f"First UV Map: {report['first_uv'].name}")
			box.label(text=f"Second UV Map: {report['second_uv'].name}")
		else:
			box.label(text=f"UV Map: {report['first_uv'].name}")

		layout.label(text="Morph Snapping Options:")
		layout.prop(self, "snapping_enabled")
		box = layout.box()
		box.prop(self, "snapping_range")
		box.prop(self, "snap_lerp_coeff")
		box.prop(self, "snap_delta_positions")
		box_row = box.row()
		box_row.prop(self, "snap_lerp_coeff_delta_positions")

		box_row.enabled = False
		box.enabled = False
		if self.snapping_enabled:
			box.enabled = True
			if self.snap_delta_positions:
				box_row.enabled = True

	def execute(self, context):
		_try_import_success, _rtn_str = utils._try_import("import scipy", "Scipy not installed. Install it in Plugin Preferences Panel.", raise_exception=False)
		if not _try_import_success:
			self.report({'ERROR'}, _rtn_str)
			return {'CANCELLED'}
		
		if self.snapping_enabled:
			rtn, _ = MorphIO.ExportMorph_alt(self, context, self.filepath, self, self.snapping_range, self.snap_delta_positions, self.snap_lerp_coeff, self.snap_lerp_coeff_delta_positions)
		else:
			rtn, _ = MorphIO.ExportMorph_alt(self, context, self.filepath, self)
		return rtn

	def invoke(self, context, event):
		self.filename = "morph.dat"

		if os.path.isdir(os.path.dirname(self.filepath)):
			self.filepath = os.path.join(os.path.dirname(self.filepath),self.filename)

		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}
	
__classes__ = [
	ImportCustomMorph,
    ExportCustomMorph,
]

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

def register():
    for cls in __classes__:
        bpy.utils.register_class(cls)
		
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import_morph)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export_morph)
		
def unregister():
    for cls in __classes__:
        bpy.utils.unregister_class(cls)

    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_morph)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_morph)