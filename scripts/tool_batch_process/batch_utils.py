import bpy, os, subprocess, NifIO, MorphIO


"""

Returns plugin folders read from disk.
"""

def getPluginFolders():

    batch = os.path.join(os.path.dirname(os.path.abspath(__file__)), "batch_files")
    folders = []
    
    for idx, f in enumerate(os.listdir(batch)):
        folders.append(tuple((str(idx), f, f)))

    return folders

"""

Imports nif from batch list with all morphs.
"""

def importFromBatchList(self, context, batch_list_item):
    assets = self.assets_folder

    for armor_addon in batch_list_item.armor_addons:
        models = [
            armor_addon.world_male,
            armor_addon.fp_male,
            armor_addon.world_female,
            armor_addon.fp_female
        ]

        for idx, model in enumerate(models):
            if len(model) == 0:
                continue

            nif = model[0].nif
            
            if idx <= 1:
                self.skeleton_name = "skeleton_male"
            else:
                self.skeleton_name = "skeleton_female"

            NifIO.ImportNif(
                os.path.join(assets, "meshes", nif),
                self,
                context,
                self
            )

            if model[0].chargen_morph in ["", None]:
                continue
            
            self.filepath = os.path.join(assets, model[0].chargen_morph, "morph.dat")

            MorphIO.ImportMorph(self, context, self)

            for obj in [obj for obj in bpy.context.scene.objects if obj in bpy.context.selected_objects]:
                obj.select_set(False)


"""

Generate outfit JSON file using genoutfit.exe.
"""

def generateOutfitJson(plugin_path, gen_folder=None):
    if not os.path.isfile(plugin_path):
        return False
    
    addon_folder = os.path.dirname(os.path.abspath(__file__))
    
    if gen_folder == None:

        gen_folder = os.path.join(
            addon_folder,
            "batch_files"
        )
    
    if not os.path.isdir(gen_folder):
        os.makedirs(gen_folder)
    
    args = [
        os.path.join(addon_folder, "gen_outfit", "genoutfit.exe"),
        f"plugin={str(plugin_path).replace(os.sep, '/')}",
        f"gen_folder={str(gen_folder).replace(os.sep, '/')}",
        f"overwrite=true"
    ]

    subprocess.run(args, stdout=subprocess.PIPE, cwd=gen_folder)

    return True