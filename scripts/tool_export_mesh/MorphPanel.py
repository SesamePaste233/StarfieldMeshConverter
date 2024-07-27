import bpy

import utils_blender

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

__classes__ = [
	SGB_UL_ShapeKeyListItems,
	shapeKeyList,
	TransferShapeKeys,
	MorphListRecalculateNormals
]

def register():
    for cls in __classes__:
        bpy.utils.register_class(cls)

    bpy.types.DATA_PT_shape_keys.append(menu_func_morphs)
	
def unregister():
    for cls in __classes__:
        bpy.utils.unregister_class(cls)

    bpy.types.DATA_PT_shape_keys.remove(menu_func_morphs)