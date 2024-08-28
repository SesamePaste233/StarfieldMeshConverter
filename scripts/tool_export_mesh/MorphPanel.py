import bpy
from bpy.types import Context

import utils_blender
import utils_common as utils

import utils_morph_attrs

import numpy as np
from numpy.linalg import LinAlgError

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
		_try_import_success, _rtn_str = utils._try_import("import scipy", "Scipy not installed. Install it in Plugin Preferences Panel.", raise_exception=False)
		if not _try_import_success:
			self.report({'ERROR'}, _rtn_str)
			return {'CANCELLED'}
		
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

class MorphListCreateResetNormals(bpy.types.Operator):
	bl_idname = "object.morph_list_create_reset_normals"
	bl_label = "Create Normals"
	bl_description = "Create custom morph normals for this shape-key."
	
	@classmethod
	def poll(cls, context):
		return True
	
	def execute(self, context):
		obj = context.object
		mesh:bpy.types.Mesh = obj.data
		mn = utils_morph_attrs.MorphNormals()
		shapekey_name = mesh.shape_keys.key_blocks[obj.active_shape_key_index].name

		bpy.ops.ed.undo_push()

		mn.validate_all(mesh)

		rtn = (mn.create(mesh, shapekey_name, replace=True) is not None)

		mn.set_data_foreach(mesh, shapekey_name, np.array([0.0, 0.0, 0.0]))

		if rtn == False:
			self.report({'ERROR'}, "Shape-key for adding normals not found.")
			return {'CANCELLED'}

		self.report({'INFO'}, f"Added normals for {shapekey_name}")
		
		return {'FINISHED'}

	def invoke(self, context, event):
		return context.window_manager.invoke_props_dialog(self)

class MorphListCreateResetColors(bpy.types.Operator):
	bl_idname = "object.morph_list_create_reset_colors"
	bl_label = "Create Colors"
	bl_description = "Create custom morph colors for this shape-key."
	
	color_rgb: bpy.props.FloatVectorProperty(
		name="Color",
		subtype='COLOR',
		size=3,
		default=(1.0, 1.0, 1.0),
		min=0.0,
		max=1.0,
	)

	@classmethod
	def poll(cls, context):
		return True
	
	def draw(self, context: Context):
		layout = self.layout

		layout.prop(self, "color_rgb")

	def execute(self, context):
		obj = context.object
		mesh:bpy.types.Mesh = obj.data
		mtc = utils_morph_attrs.MorphTargetColors()
		shapekey_name = mesh.shape_keys.key_blocks[obj.active_shape_key_index].name

		bpy.ops.ed.undo_push()

		mtc.validate_all(mesh)

		col_attr = mtc.create(mesh, shapekey_name, replace=True)

		mtc.set_data_foreach(mesh, shapekey_name, np.array(list(self.color_rgb) + [1.0]))

		if col_attr is None:
			self.report({'ERROR'}, "Shape-key for adding colors not found.")
			return {'CANCELLED'}
		
		utils_blender.set_viewport_shading(context.screen, type='SOLID', color_type='VERTEX')

		mesh.attributes.active_color = col_attr

		self.report({'INFO'}, f"Added colors for {shapekey_name}")
		
		return {'FINISHED'}

	def invoke(self, context, event):
		return context.window_manager.invoke_props_dialog(self)

class MorphListSelectNormals(bpy.types.Operator):
	bl_idname = "object.morph_list_select_normals"
	bl_label = "Select Normal"
	bl_description = "Select normal attribute for this shape-key."

	@classmethod
	def poll(cls, context):
		return True
	
	def execute(self, context):
		obj = context.object
		mesh:bpy.types.Mesh = obj.data

		bpy.ops.ed.undo_push()

		nrm_attr = utils_morph_attrs.MorphNormals().validate(mesh, mesh.shape_keys.key_blocks[obj.active_shape_key_index].name)

		if nrm_attr is None:
			self.report({'ERROR'}, "Shape-key for selecting normals not found.")
			return {'CANCELLED'}
		
		mesh.attributes.active = nrm_attr

		self.report({'INFO'}, f"Selected normals for {obj.data.shape_keys.key_blocks[obj.active_shape_key_index].name}")
		
		return {'FINISHED'}

class MorphListSelectColor(bpy.types.Operator):
	bl_idname = "object.morph_list_select_color"
	bl_label = "Select Color"
	bl_description = "Select color attribute for this shape-key."

	@classmethod
	def poll(cls, context):
		return True
	
	def execute(self, context):
		obj = context.object
		mesh:bpy.types.Mesh = obj.data

		bpy.ops.ed.undo_push()

		col_attr = utils_morph_attrs.MorphTargetColors().validate(mesh, mesh.shape_keys.key_blocks[obj.active_shape_key_index].name)

		if col_attr is None:
			self.report({'ERROR'}, "Shape-key for selecting colors not found.")
			return {'CANCELLED'}
		
		utils_blender.set_viewport_shading(context.screen, type='SOLID', color_type='VERTEX')

		mesh.attributes.active_color = col_attr

		self.report({'INFO'}, f"Selected colors for {obj.data.shape_keys.key_blocks[obj.active_shape_key_index].name}")
		
		return {'FINISHED'}
	

def menu_func_morph_attrs(self, context):
	layout:bpy.types.UILayout = self.layout
	layout.separator()

	obj = context.object
	if obj.data.shape_keys == None or len(obj.data.shape_keys.key_blocks) == 0 or obj.active_shape_key_index == 0:
		return

	col = layout.column()

	sk = obj.data.shape_keys.key_blocks[obj.active_shape_key_index]
	col.label(text=f"Morph Attributes: {sk.name}")

	nrm_attr = utils_morph_attrs.MorphNormals().validate(obj.data, sk.name, )
	nrm_found = (nrm_attr is not None)

	col_attr = utils_morph_attrs.MorphTargetColors().validate(obj.data, sk.name, )
	col_found = (col_attr is not None)

	row = layout.row(align=True)
	row.label(text=f"Morph Delta Normal")
	row.label(text=f"Morph Target Color")

	row = layout.row(align=True)
	row.label(text=f"Attr: {nrm_attr.name if nrm_found else 'Not Found'}")
	row.label(text=f"Attr: {col_attr.name if col_found else 'Not Found'}")
	
	row = layout.row(align=True)
	col1 = row.column(align=True)
	col2 = row.column(align=True)
	col1.operator(MorphListCreateResetNormals.bl_idname, text=f"{'Create Normals' if not nrm_found else 'Reset Normals'}")
	col2.operator(MorphListCreateResetColors.bl_idname, text=f"{'Create Colors' if not col_found else 'Reset Colors'}")

	row = layout.row(align=True)
	col1 = row.column(align=True)
	col2 = row.column(align=True)
	if not nrm_found:
		col1.enabled = False
	if not col_found:
		col2.enabled = False
	col1.operator(MorphListSelectNormals.bl_idname, text="Select Normal Attr")
	col2.operator(MorphListSelectColor.bl_idname, text="View Color Attr")


def menu_func_transfer_shape_keys(self, context):
	layout:bpy.types.UILayout = self.layout
	layout.separator()

	obj = context.object
	if obj.data.shape_keys == None or len(obj.data.shape_keys.key_blocks) == 0:
		return

	row = layout.row(align=True)
	#row.operator("object.morph_list_recalculate_normals")
	row.operator(TransferShapeKeys.bl_idname)


__classes__ = [
	SGB_UL_ShapeKeyListItems,
	shapeKeyList,
	TransferShapeKeys,
	MorphListCreateResetNormals,
	MorphListCreateResetColors,
	MorphListSelectNormals,
	MorphListSelectColor,
]

__menu_funcs__ = {
	bpy.types.DATA_PT_shape_keys: [
		menu_func_morph_attrs,
		menu_func_transfer_shape_keys,
	],
}

def register():
	for cls in __classes__:
		bpy.utils.register_class(cls)

	for cls, funcs in __menu_funcs__.items():
		for func in funcs:
			cls.append(func)
	
def unregister():
	for cls in __classes__:
		bpy.utils.unregister_class(cls)

	for cls, funcs in __menu_funcs__.items():
		for func in funcs:
			cls.remove(func)