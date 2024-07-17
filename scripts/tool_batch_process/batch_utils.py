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
            
            world_model = idx % 2 == 0
            fp_model = not world_model

            excl_m = idx <= 1 and self.batch_m == False
            excl_f = idx >= 2 and self.batch_f == False
            
            excl_world = world_model and self.batch_world_model == False
            excl_fp = fp_model and self.batch_first_person_model == False

            excl_match = any((
                excl_m, excl_f,
                excl_world, excl_fp
            ))

            if excl_match:
                continue

            if idx <= 1:
                self.skeleton_name = "skeleton_male"
            else:
                self.skeleton_name = "skeleton_female"

            nif = model[0].nif

            NifIO.ImportNif(
                os.path.join(assets, "meshes", nif),
                self,
                context,
                self
            )
            
            morphs = []

            if self.batch_chargen_morph and model[0].chargen_morph != "":
                morphs.append(os.path.join(assets, model[0].chargen_morph, "morph.dat"))

            if self.batch_perf_morph and model[0].performance_morph != "":
                morphs.append(os.path.join(assets, model[0].performance_morph, "morph.dat"))
            
            for morph in morphs:
                self.filepath = morph

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