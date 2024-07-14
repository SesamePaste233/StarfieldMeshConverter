import bpy, os, json

from bpy.props import CollectionProperty, StringProperty, IntProperty, BoolProperty, EnumProperty, FloatProperty


"""
Utilitary functions for correcting input data.
"""

def setAssetsFolder(self, value):
    self["assets_folder"] = bpy.path.abspath(value)

def getAssetsFolder(self):
    if "assets_folder" in self.keys():
        return self["assets_folder"]
    return ""

def pluginListIndexUpdate(self, context):
    bpy.context.scene.batch_list_index = 0


"""
UI property classes.
"""

class ArmorAddonData(bpy.types.PropertyGroup):
    nif: StringProperty(name="Nif path", default="")
    chargen_morph: StringProperty(name="Chargen morph path", default="")
    performance_morph: StringProperty(name="Performance morph path", default="")

class ArmorAddons(bpy.types.PropertyGroup):
    name: StringProperty(name="Armor addon name", default="")

    world_male: CollectionProperty(type=ArmorAddonData)
    world_female: CollectionProperty(type=ArmorAddonData)

    fp_male: CollectionProperty(type=ArmorAddonData)
    fp_female: CollectionProperty(type=ArmorAddonData)

class BatchListItem(bpy.types.PropertyGroup):
    name: StringProperty(name="Outfit name", default="")
    file_name: StringProperty(name="Outfit json file name", default="")
    mod: StringProperty(name="Mod name", default="")
    form_key: StringProperty(name="Form key", default="")
    race: StringProperty(name="Form key", default="")
    armor_addons: CollectionProperty(name="Armor addons", type=ArmorAddons)

class StarfieldPluginItem(bpy.types.PropertyGroup):
    name: StringProperty(name="Plugin name", default="")
    plugin_items: CollectionProperty(type=BatchListItem)

class AssetFolderOverride(bpy.types.PropertyGroup):
    name: StringProperty(name="Plugin name", default="")
    assets_folder: StringProperty(name="Assets", default="", subtype='DIR_PATH', get=getAssetsFolder, set=setAssetsFolder)


"""
UI panels
"""

class SGB_UL_BatchList(bpy.types.UIList):
    bl_idname = "SGB_UL_BatchList"
    layout_type = "DEFAULT"

    def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
        layout.prop(item, "name", text="", emboss=False)

class SGB_UL_PluginList(bpy.types.UIList):
    bl_idname = "SGB_UL_PluginList"
    layout_type = "DEFAULT"

    def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
        layout.alignment = 'CENTER'
        layout.label(text=item.name)
        layout.label(text=f"{str(len(item.plugin_items))} Outfits")

class SGB_PT_Batch(bpy.types.Panel):
    bl_idname = "SGB_PT_Batch"

    bl_label = "Batch processing list"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = 'Tool'

    def draw(self, context):
        layout = self.layout
        
        layout.separator()

        layout.template_list(
            "SGB_UL_PluginList",
            "",
            context.scene, "plugin_list",
            context.scene, "plugin_list_index",
            type='GRID',
			rows=1,
			columns=2
        )

        layout.operator("scene.refresh_batch_list")

        if len(context.scene.plugin_list) >= 1 and len(context.scene.plugin_list[bpy.context.scene.plugin_list_index].plugin_items) >= 1:

            plugin = context.scene.plugin_list[bpy.context.scene.plugin_list_index]

            layout.template_list(
                "SGB_UL_BatchList",
                "",
                plugin, "plugin_items",
                context.scene, "batch_list_index"
            )

            layout.operator("scene.import_from_batch_list")

            layout.prop(
                context.scene.assets_folder_override[context.scene.assets_folder_override.find(plugin.name)],
                "assets_folder",
                text=f"{plugin.name} assets"
            )

            layout.separator()

            if len(plugin.plugin_items) >= 1:

                item = bpy.context.scene.plugin_list[bpy.context.scene.plugin_list_index].plugin_items[bpy.context.scene.batch_list_index]
                col = layout.column()

                row = col.row(align=True)
                row.label(text="File Name")
                row.scale_x = 2.3
                row.label(text=item.file_name)

                row = col.row(align=True)
                row.label(text="Mod")
                row.scale_x = 2.3
                row.label(text=item.mod)

                row = col.row(align=True)
                row.label(text="Form key")
                row.scale_x = 2.3
                row.label(text=item.form_key)

                row = col.row(align=True)
                row.label(text="Race")
                row.scale_x = 2.3
                row.label(text=item.race)

                row = col.row(align=True)
                row.label(text="Armor Addons")
                row.scale_x = 2.3
                row.label(text=str(len(item.armor_addons)))
        
        layout.operator("scene.gen_outfit_json")

"""
Functions used in UI only.
"""

"""

Refreshes batch list.
"""

def refreshBatchList(batch_folder="", options=None):
    default_batch_folder = os.path.join(os.path.dirname(os.path.abspath(__file__)), "batch_files")

    if (batch_folder == None or not os.path.isdir(batch_folder)):
        if os.path.isdir(default_batch_folder):
            batch_folder = default_batch_folder
        else:
            return False
    
    bpy.context.scene.plugin_list.clear()

    if options == None:
        options = {
            "skip_empty_armor_addons": True,
            "valid_race": "00347D"
        }

    assets_folder_plugins = [p.name for p in bpy.context.scene.assets_folder_override]

    for plugin_folder in os.listdir(batch_folder):

        if plugin_folder not in assets_folder_plugins:
            assets_folder_override = bpy.context.scene.assets_folder_override.add()
            assets_folder_override.name = plugin_folder

        plugin_item = bpy.context.scene.plugin_list.add()
        plugin_item.name = plugin_folder

        plugin_path = os.path.join(batch_folder, plugin_folder)

        for json_file_name in os.listdir(plugin_path):
            json_path = os.path.join(plugin_path, json_file_name)

            if not os.path.isfile(json_path):
                continue

            json_file = json.load(open(json_path))

            if options["skip_empty_armor_addons"] and json_file["ArmorAddons"] == {}:
                continue
            
            if options["valid_race"] != "" and json_file["Race"] != options["valid_race"]:
                continue

            item = plugin_item.plugin_items.add()
            item.name = json_file["Name"]
            item.file_name = json_file_name
            item.mod = json_file["Mod"]
            item.form_key = json_file["FormKey"]
            item.race = json_file["Race"]

            if json_file["ArmorAddons"] != {}:
                for name, json_armor_addon in json_file["ArmorAddons"].items():
                    genArmorAddon(json_armor_addon, item, name)
    
    bpy.context.scene.batch_list_index = 0
    bpy.context.scene.plugin_list_index = 0
    return True

"""

Fills UI list with armor addon data.
"""

def genArmorAddon(json_armor_addon, item, name):
    body_type_list = ["M", "F"]
    model_type_list = ["WorldModel", "FirstPersonModel"]
    morph_type_list = ["ChargenMorph", "PerformanceMorph"]
    
    armor_addon = item.armor_addons.add()
    armor_addon.name = name

    for model_type in model_type_list:
        if model_type not in json_armor_addon.keys():
            continue

        for body_type in body_type_list:
            nif_found = "Nif" in json_armor_addon[model_type][body_type]

            if not nif_found or nif_found and json_armor_addon[model_type][body_type]["Nif"] == None:
                continue

            if model_type == "WorldModel":
                if body_type == "M":
                    model = armor_addon.world_male.add()
                else:
                    model = armor_addon.world_female.add()
            else:
                if body_type == "M":
                    model = armor_addon.fp_male.add()
                else:
                    model = armor_addon.fp_female.add()

            model.nif = json_armor_addon[model_type][body_type]["Nif"]

            for morph_type in morph_type_list:
                morph_found = morph_type in json_armor_addon[model_type][body_type]
                morph_valid = morph_found and json_armor_addon[model_type][body_type][morph_type] != None

                if morph_valid:
                    match morph_type:
                        case "ChargenMorph":
                            model.chargen_morph = json_armor_addon[model_type][body_type][morph_type]
                        case "PerformanceMorph":
                            model.performance_morph = json_armor_addon[model_type][body_type][morph_type]

classes = [
    ArmorAddonData,
    ArmorAddons,
    BatchListItem,
    StarfieldPluginItem,
    AssetFolderOverride,

    SGB_UL_BatchList,
    SGB_UL_PluginList,
    SGB_PT_Batch,
]

def register():
    for c in classes:
        bpy.utils.register_class(c)
    
    s = bpy.types.Scene
    o = bpy.types.Object

    s.plugin_list = CollectionProperty(type=StarfieldPluginItem)
    s.plugin_list_index = IntProperty(name="Index", default=0, update=pluginListIndexUpdate)
    s.batch_list_index = IntProperty(name="Index", default=0)
    s.assets_folder_override = CollectionProperty(type=AssetFolderOverride)

    s.active_armor_addon_index = IntProperty(name="Index", default=0)

def unregister():
    for c in classes:
        bpy.utils.unregister_class(c)
    
    s = bpy.types.Scene
    o = bpy.types.Object

    del s.plugin_list
    del s.plugin_list_index
    del s.batch_list_index
    del s.assets_folder_override
    del s.active_armor_addon_index
