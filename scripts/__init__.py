import bpy
import os
import subprocess
import shutil
import bmesh
import json
import hashlib
import datetime
import re


bl_info = {
    "name": "Starfield Mesh Exporter",
    "version": (1, 0, 0),
    "blender": (3, 0, 0),
    "location": "File > Import-Export",
    "description": "Export .mesh geometry file for starfield.",
    "warning": "",
    "category": "Import-Export",
    }

def hash_string(input_string):
    # Create a SHA-1 hash object
    sha1 = hashlib.sha1()

    # Update the hash object with the input string encoded as bytes
    sha1.update(input_string.encode('utf-8'))

    # Get the hexadecimal representation of the hash
    hex_digest_input = sha1.hexdigest()

    # Take the first 20 characters of the input string's hexadecimal digest
    hex_result_input = hex_digest_input[:20]

    # Get the current date and time as a string
    current_datetime = datetime.datetime.now().strftime('%Y%m%d%H%M%S%f')

    # Create a SHA-1 hash object for the current date and time
    sha1 = hashlib.sha1()

    # Update the hash object with the current date and time encoded as bytes
    sha1.update(current_datetime.encode('utf-8'))

    # Get the hexadecimal representation of the hash
    hex_digest_datetime = sha1.hexdigest()

    # Take the first 20 characters of the datetime's hexadecimal digest
    hex_result_datetime = hex_digest_datetime[:20]

    # Combine the two hexadecimal results
    return hex_result_datetime, hex_result_input

def hash_string_2(input_string):
    # Create a SHA-1 hash object
    sha1 = hashlib.sha1()

    # Update the hash object with the input string encoded as bytes
    sha1.update(input_string.encode('utf-8'))

    # Get the hexadecimal representation of the hash
    hex_digest_input = sha1.hexdigest()

    # Take the first 20 characters of the input string's hexadecimal digest
    hex_result_input = hex_digest_input[:20]

    # Get the current timestamp as an integer
    current_timestamp = int(datetime.datetime.now().timestamp())

    # Convert the prefix and timestamp to integers
    prefix = int("fffff000000000000000", 16)
    timestamp = current_timestamp

    # Add the two integers together
    result = prefix + timestamp

    # Convert the result back to a 20-character hexadecimal string
    hex_result_datetime = format(result, '020x')

    # Combine the two hexadecimal results
    return hex_result_datetime, hex_result_input


def open_folder(initial_directory):

    # Set the window manager to the current context
    wm = bpy.context.window_manager

    # Call the file browser operator
    bpy.ops.wm.path_open(filepath=initial_directory)
                         
def copy_and_rename_file(source_file, destination_folder, new_file_name):
    # Extract the file name and extension
    file_name, file_extension = os.path.splitext(source_file)

    # Construct the destination path
    destination_path = os.path.join(destination_folder, new_file_name + '.mesh')
    
    shutil.copy2(source_file, destination_path)

def update_path(utils_p):
    utils_path = bpy.path.abspath(utils_p)
    temp_path = os.path.join(utils_path, 'Temp')
    
    return utils_path,temp_path

def delete_folder(path):
    try:
        shutil.rmtree(path)
        print(f"Folder '{path}' and its contents have been successfully deleted.")
    except FileNotFoundError:
        print(f"Folder '{path}' does not exist.")
    except Exception as e:
        print(f"An error occurred while deleting the folder '{path}': {e}")

def flatten(lst):
    result = []
    for item in lst:
        if isinstance(item, list):
            result.extend(flatten(item))
        else:
            result.append(item)
    return result
# Define a list of items with labels
export_items = [
    ("GEO", "Geometry", "Export geometry data (positions and indices)."),
    ("NORM", "Normals", "Export normals data."),
    ("UV", "UV", "Export texture coordinates data."),
    ("VERTCOLOR", "Vertex Color", "Export vertex color data."),
    ("WEIGHTS", "Weights", "Export vertex groups data."),
]

class ExportSFMeshOperator(bpy.types.Operator):
    """Export the active object"""
    bl_idname = "export.sfmesh"
    bl_label = "Export Active Mesh"
    
    folder_path: bpy.props.StringProperty(subtype="DIR_PATH", default="")

    def execute(self, context):
        # Check if the folder path is valid
        utils_path, temp_path = update_path(os.path.dirname(__file__))
        
        if not os.path.isdir(temp_path):
            os.makedirs(temp_path)

        old_obj = bpy.context.active_object
        if old_obj:
            active_object_name = bpy.context.active_object.name
            new_obj = old_obj.copy()
            new_obj.data = old_obj.data.copy()
            new_obj.animation_data_clear()
            bpy.context.collection.objects.link(new_obj)
            
            bpy.ops.object.mode_set(mode='EDIT')
            
            # Select all edges
            bpy.ops.mesh.select_all(action='SELECT')
            
            # Switch to Edge Select mode in UV Editor
            bpy.ops.uv.select_all(action='SELECT')
            
            bpy.ops.uv.seams_from_islands()
            
            
            bpy.ops.object.mode_set(mode='OBJECT')
            
            # Add a Data Transfer modifier to the new object
            data_transfer_modifier = new_obj.modifiers.new(name="Data Transfer", type='DATA_TRANSFER')
            data_transfer_modifier.use_loop_data = True
            data_transfer_modifier.data_types_loops = {'CUSTOM_NORMAL'}   # Copy vertex normals

            data_transfer_modifier.object = old_obj

            # Apply the Data Transfer modifier
            bpy.context.view_layer.objects.active = new_obj
            bpy.ops.object.modifier_apply(modifier=data_transfer_modifier.name)
            
            selected_obj = new_obj
            
        else:
            print("No object is selected.")
            selected_obj = None
            return {'CANCELLED'}

        # Check if the selected object is a mesh
        if selected_obj and selected_obj.type == 'MESH':
            # Create a BMesh from the selected object
            bm = bmesh.new()
            bm.from_mesh(selected_obj.data)
            
            uv_layer = bm.loops.layers.uv.active
            
            
            seams = [e for e in bm.edges if e.seam]
            # split on seams
            bmesh.ops.split_edges(bm, edges=seams)
            
            # Triangulate the mesh
            bmesh.ops.triangulate(bm, faces=bm.faces)
            # Initialize dictionaries to store data
            data = {
                "positions": [],
                "positions_raw": [],
                "vertex_indices": [],
                "vertex_indices_raw": [],
                "normals": [],
                "uv_coords": [],
                "vertex_color": [],
                "bone_list":[],
                "vertex_weights": []
            }
            # Extract data from the mesh
            color_layer = bm.loops.layers.color.active
            for v in bm.verts:
                #data["positions"].append(list(v.co))
                if context.scene.GEO:
                    data["positions_raw"].extend(list(v.co))
                if context.scene.NORM:
                    data["normals"].append(list(v.normal))
                loop = v.link_loops[0]
                
                if context.scene.VERTCOLOR and color_layer:
                    data["vertex_color"].append([loop[color_layer][0],loop[color_layer][1],loop[color_layer][2],loop[color_layer][3]])
            
            if context.scene.UV:
                data["uv_coords"] = [[] for i in bm.verts]
                for face in bm.faces:
                    for vert, loop in zip(face.verts, face.loops):
                        data["uv_coords"][vert.index] = [loop[uv_layer].uv[0], loop[uv_layer].uv[1]]
            
            if context.scene.GEO:
                for f in bm.faces:
                    #data["vertex_indices"].append([v.index for v in f.verts])
                    data["vertex_indices_raw"].extend([v.index for v in f.verts])

            # Extract vertex weights and bones
            if context.scene.WEIGHTS:
                vertex_groups = selected_obj.vertex_groups
                vgrp_names = [vg.name for vg in vertex_groups]
                data["bone_list"] = vgrp_names
                
                bm.verts.layers.deform.verify()

                deform = bm.verts.layers.deform.active
                
                for v in bm.verts:
                    g = v[deform]
                    
                    if len(g.items()) > 0 :
                        data["vertex_weights"].append(g.items())

            # Save the data to a JSON file
            output_file = os.path.join(temp_path, "mesh_data.json")
            with open(output_file, 'w') as json_file:
                json.dump(data, json_file, indent=4)
            print(f"Data saved to {output_file}")

            # Cleanup
            bm.to_mesh(selected_obj.data)
            bm.free()
        else:
            print("Selected object is not a mesh.")
            return {'CANCELLED'}

        if selected_obj:
            bpy.context.view_layer.objects.active = old_obj
            bpy.data.meshes.remove(selected_obj.data)
            try:
                if context.scene.export_sf_mesh_hash_result:
                    hash_folder, hash_name = hash_string(active_object_name)
                    result_file_folder = os.path.join(bpy.path.abspath(context.scene.export_mesh_folder_path), active_object_name, hash_folder)
                    os.makedirs(result_file_folder)
                    result_file_path = os.path.join(result_file_folder, hash_name + ".mesh")
                else:
                    result_file_path = os.path.join(bpy.path.abspath(context.scene.export_mesh_folder_path), active_object_name + ".mesh")
                
                log_file_path = os.path.join(utils_path, "console.log")
                with open(log_file_path, "w") as log_file:
                    result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                                    os.path.join(temp_path, "mesh_data.json"),
                                    result_file_path,
                                    str(context.scene.mesh_scale),
                                    ],stdout=log_file)


                if result.returncode == 0:
                    self.report({'INFO'}, "Starfield .mesh exported successfully")
                    
                else:
                    self.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
                    return {'CANCELLED'}
                
            except subprocess.CalledProcessError as e:
                self.report({'WARN'}, f"Execution failed with return code {e.returncode}: {e.stderr}")
            except FileNotFoundError:
                self.report({'WARN'}, "Executable not found.")

            if context.scene.export_sf_mesh_open_folder == True:
                open_folder(bpy.path.abspath(context.scene.export_mesh_folder_path))

            return {'FINISHED'}

        return {'CANCELLED'}

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

        # Export settings
        layout.label(text="Export Settings:")
        layout.prop(context.scene, "mesh_scale", text="Scale")
        
        
        # Create a checkbox for each item
        for item in export_items:
            layout.prop(context.scene, item[0], text=item[1])
           
        layout.label(text="After Export:") 
        layout.prop(context.scene, "export_sf_mesh_open_folder", text="Open export folder")
        layout.prop(context.scene, "export_sf_mesh_hash_result", text="Hash file name")
        # Button to export the selected skeleton
        layout.operator("export.sfmesh", text="Export .mesh")


def register():
    bpy.types.Scene.export_mesh_folder_path = bpy.props.StringProperty(
        name="Export Folder",
        subtype='DIR_PATH',
        default=os.path.join(os.path.dirname(__file__),'Result'),
    )
    bpy.types.Scene.mesh_scale = bpy.props.FloatProperty(
        name="Scale",
        default=1,
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
    bpy.types.Scene.UV = bpy.props.BoolProperty(
        name="UV",
        description=export_items[2][2],
        default=True
    )
    bpy.types.Scene.VERTCOLOR = bpy.props.BoolProperty(
        name="Vertex Color",
        description=export_items[3][2],
        default=True
    )
    bpy.types.Scene.WEIGHTS = bpy.props.BoolProperty(
        name="Weights",
        description=export_items[4][2],
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
    bpy.utils.register_class(ExportSFMeshOperator)
    bpy.utils.register_class(ExportSFMeshPanel)


def unregister():
    bpy.utils.unregister_class(ExportSFMeshOperator)
    bpy.utils.unregister_class(ExportSFMeshPanel)
    del bpy.types.Scene.export_mesh_folder_path
    del bpy.types.Scene.mesh_scale
    del bpy.types.Scene.GEO
    del bpy.types.Scene.NORM
    del bpy.types.Scene.VERTCOLOR
    del bpy.types.Scene.UV
    del bpy.types.Scene.WEIGHTS
    del bpy.types.Scene.export_sf_mesh_open_folder

if __name__ == "__main__":
    register()
