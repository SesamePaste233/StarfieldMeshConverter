import bpy
import os
import subprocess
import shutil
import bmesh
import json
import hashlib
import datetime
from collections import defaultdict
import mathutils
import numpy as np
from mathutils import Color


bl_info = {
    "name": "Starfield Mesh Exporter",
    "version": (0, 5, 0),
    "blender": (3, 5, 0),
    "location": "File > Import-Export",
    "description": "Export .mesh geometry file for starfield.",
    "warning": "",
    "category": "Import-Export",
    }

def sanitize_filename(filename):
    illegal_chars = ['<', '>', ':', '"', '/', '\\', '|', '?', '*']
    replacement_char = '_'  # You can replace illegal characters with another character or remove them

    # Replace illegal characters with the replacement character
    for char in illegal_chars:
        filename = filename.replace(char, replacement_char)

    return filename

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

def ExportMesh(options, context, filepath, operator):
    export_mesh_file_path = filepath
    export_mesh_folder_path = os.path.dirname(export_mesh_file_path)
    utils_path, temp_path = update_path(os.path.dirname(__file__))
    
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
        "vertex_weights": [],
        "smooth_group": []
    }

    if not os.path.isdir(temp_path):
        os.makedirs(temp_path)

    old_obj = bpy.context.active_object
    if old_obj and old_obj.type == 'MESH':
        
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
        
        bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
        bpy.ops.mesh.select_all(action='DESELECT')
        bpy.ops.mesh.select_non_manifold(extend=False, use_boundary=True)
        bpy.ops.mesh.edge_split(type='EDGE')
        bpy.ops.mesh.select_all(action='DESELECT')
        
        bpy.ops.object.mode_set(mode='OBJECT')
        
        # Add a Data Transfer modifier to the new object
        data_transfer_modifier = new_obj.modifiers.new(name="Data Transfer", type='DATA_TRANSFER')
        data_transfer_modifier.use_loop_data = True
        data_transfer_modifier.data_types_loops = {'CUSTOM_NORMAL'}   # Copy vertex normals

        data_transfer_modifier.object = old_obj

        # Apply the Data Transfer modifier
        bpy.context.view_layer.objects.active = new_obj
        bpy.ops.object.modifier_apply(modifier=data_transfer_modifier.name)

        if options.use_world_origin:
            old_obj.select_set(False)
            new_obj.select_set(True)
            bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
            old_obj.select_set(True)
        
        

        selected_obj = new_obj
        
    else:
        print("No valid object is selected.")
        selected_obj = None
        return {'CANCELLED'}

    # Check if the selected object is a mesh
    if selected_obj and selected_obj.type == 'MESH':
        # Create a BMesh from the selected object
        bm = bmesh.new()
        bm.from_mesh(selected_obj.data)
        
        uv_layer = bm.loops.layers.uv.active
        
        seams = [e for e in bm.edges if e.seam or not e.smooth]
        # split on seams
        bmesh.ops.split_edges(bm, edges=seams)
        
        # Triangulate the mesh
        bmesh.ops.triangulate(bm, faces=bm.faces)

        bm.to_mesh(selected_obj.data)
        bm.free()

        #bpy.ops.wm.obj_export(filepath = os.path.join(temp_path, "mesh_data.obj"), export_materials=False,export_selected_objects = True)

        # Create a list to store the vertex indices of sharp edges
        sharp_edge_vertices = []

        # Ensure we are in Edit Mode
        if selected_obj.mode != 'EDIT':
            bpy.ops.object.mode_set(mode='EDIT')

        # Deselect all
        bpy.ops.mesh.select_all(action='DESELECT')

        _obj = bpy.context.edit_object
        _me = _obj.data

        _bm = bmesh.from_edit_mesh(_me)
        for e in _bm.edges:
            if not e.smooth:
                e.select = True
        
        bmesh.update_edit_mesh(_me)

        # Switch to Vertex Select Mode
        bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='VERT')

        # Switch back to Object Mode
        bpy.ops.object.mode_set(mode='OBJECT')

        # Iterate through selected vertices and add their indices to the list
        for vertex in selected_obj.data.vertices:
            if vertex.select:
                sharp_edge_vertices.append(vertex.index)

        data["smooth_group"] = []

        for vertex in selected_obj.data.vertices:
            if vertex.index not in sharp_edge_vertices:
                data["smooth_group"].append(vertex.index)

        if "SMOOTH_GROUP" in selected_obj.vertex_groups:
            data["smooth_group"] = []
            smooth_group = selected_obj.vertex_groups["SMOOTH_GROUP"]
            
            for vertex in selected_obj.data.vertices:
                # Check if the vertex is in the "SMOOTH_GROUP"
                for group_element in vertex.groups:
                    if group_element.group == smooth_group.index:
                        data["smooth_group"].append(vertex.index)

            # Remove the vertex group
            selected_obj.vertex_groups.remove(smooth_group)

        if "SHARP_GROUP" in selected_obj.vertex_groups:
            data["smooth_group"] = []
            sharp_group = selected_obj.vertex_groups["SHARP_GROUP"]

            for vertex in selected_obj.data.vertices:
                is_sharp = False
                for group_element in vertex.groups:
                    if group_element.group == sharp_group.index:
                        is_sharp = True
                        break
                
                if not is_sharp and vertex.index not in sharp_edge_vertices:
                    data["smooth_group"].append(vertex.index)

            selected_obj.vertex_groups.remove(sharp_group)
            
        bm = bmesh.new()
        bm.from_mesh(selected_obj.data)

        # Extract data from the mesh
        color_layer = bm.loops.layers.color.active
        verts_count = 0
        for v in bm.verts:
            verts_count += 1
            #data["positions"].append(list(v.co))
            if options.GEO:
                data["positions_raw"].extend(list(v.co))
            if options.NORM:
                data["normals"].append(list(v.normal))

            
            if options.VERTCOLOR and color_layer:
                loop = v.link_loops[0]
                data["vertex_color"].append([loop[color_layer][0],loop[color_layer][1],loop[color_layer][2],loop[color_layer][3]])

        
        try:
            if options.UV and uv_layer:
                vertex_map = defaultdict(list)
                for poly in selected_obj.data.polygons:
                    for v_ix, l_ix in zip(poly.vertices, poly.loop_indices):
                        vertex_map[v_ix].append(l_ix)

                data["uv_coords"] = [[] for i in range(verts_count)]
                for face in selected_obj.data.polygons:
                    for vert_idx, loop_idx in zip(face.vertices, face.loop_indices):
                        uv_coords = selected_obj.data.uv_layers.active.data[loop_idx].uv
                        data["uv_coords"][vert_idx] = [uv_coords[0],1-uv_coords[1]]

                for _l in data["uv_coords"]:
                    if len(_l) == 0:
                        operator.report({'WARNING'}, f"UV map is invalid.")
                        print(data["uv_coords"], verts_count)
                        return {'CANCELLED'}
                    
            
            if options.GEO:
                for f in bm.faces:
                    #data["vertex_indices"].append([v.index for v in f.verts])
                    data["vertex_indices_raw"].extend([v.index for v in f.verts])

            # Extract vertex weights and bones
            if options.WEIGHTS:
                vertex_groups = selected_obj.vertex_groups
                vgrp_names = [vg.name for vg in vertex_groups]
                data["bone_list"] = vgrp_names
                
                bm.verts.layers.deform.verify()

                deform = bm.verts.layers.deform.active
                
                for v in bm.verts:
                    g = v[deform]
                    
                    if len(g.items()) > 0 :
                        data["vertex_weights"].append(g.items())
                    elif len(data["bone_list"])>0:
                        data["vertex_weights"].append([[0, 0]])


        except IndexError:
            operator.report({'WARNING'}, "The mesh may have loose vertices, try to Clean Up the mesh or contact the author.")
            return {'CANCELLED'}

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
            if options.export_sf_mesh_hash_result:
                hash_folder, hash_name = hash_string(active_object_name)
                object_folder_name = sanitize_filename(active_object_name)
                result_file_folder = os.path.join(os.path.dirname(export_mesh_file_path), object_folder_name, hash_folder)
                os.makedirs(result_file_folder)
                result_file_path = os.path.join(result_file_folder, hash_name + ".mesh")
            else:
                result_file_path = export_mesh_file_path
            
            log_file_path = os.path.join(utils_path, "console.log")
            with open(log_file_path, "w") as log_file:
                print("REPORT:",result_file_path)
                result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                                '-m',
                                os.path.join(temp_path, "mesh_data.json"),
                                result_file_path,
                                str(options.mesh_scale),
                                str(int(options.smooth_edge_normals)),
                                str(int(options.normalize_weights)),
                                ],stdout=log_file)


            if result.returncode == 0:
                operator.report({'INFO'}, "Starfield .mesh exported successfully")

                if options.export_sf_mesh_open_folder == True:
                    open_folder(bpy.path.abspath(export_mesh_folder_path))

                return {'FINISHED'}
                
            else:
                operator.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
                return {'CANCELLED'}
            
        except subprocess.CalledProcessError as e:
            operator.report({'WARNING'}, f"Execution failed with return code {e.returncode}: {e.stderr}")
            return {'CANCELLED'}
        except FileNotFoundError:
            operator.report({'WARNING'}, "Executable not found.")
            return {'CANCELLED'}

    return {'CANCELLED'}

def ImportMesh(options, context, operator):
    import_path = options.filepath
    utils_path, temp_path = update_path(os.path.dirname(__file__))

    log_file_path = os.path.join(utils_path, "console_import.log")
    with open(log_file_path, "w") as log_file:
        result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                            '-b',
                            import_path,
                            os.path.join(temp_path, "mesh_data_import"),
                            ],stdout=log_file)


    if result.returncode == 0:
        operator.report({'INFO'}, "Starfield .mesh exported successfully")
        
        bpy.ops.wm.obj_import(
            filepath=os.path.join(temp_path, "mesh_data_import.obj"),
            forward_axis='Y',
            up_axis ='Z',  # Customize other import options here
        )

        obj = bpy.context.selected_objects[0]
        if obj:
            mesh = obj.data
            if not mesh.vertex_colors:
                mesh.vertex_colors.new()

            bm = bmesh.new()
            bm.from_mesh(mesh)

            col = obj.data.vertex_colors.active

            with open(os.path.join(temp_path, "mesh_data_import.json"), 'r') as json_file:
                data = json.load(json_file)

                if len(data["vertex_weights"]) > 0:
                    num_bones_per_vert = len(data["vertex_weights"][0])
                    num_bones = -1
                    for v in bm.verts:
                        for i in range(num_bones_per_vert):
                            if data["vertex_weights"][v.index][i][0] > num_bones:
                                num_bones = data["vertex_weights"][v.index][i][0]
                    
                    num_bones += 1
                    bones = []
                    for i in range(num_bones):
                        bones.append(obj.vertex_groups.new(name='bone' + str(i)))

                    if len(bm.verts) != len(data["vertex_weights"]):
                        operator.report({'WARNING'}, f"Weight data mismatched. Contact the author for assistance.")
                        return {'CANCELLED'}
                    
                    for v in bm.verts:
                        for i in range(num_bones_per_vert):
                            cur_boneweight = data["vertex_weights"][v.index][i]
                            
                            if cur_boneweight[1] != 0:
                                bones[int(cur_boneweight[0])].add([v.index], cur_boneweight[1],'ADD')
                        #print(v.index, v.co, data["vertex_weights"][v.index])

                vertex_map = defaultdict(list)
                for poly in obj.data.polygons:
                    for v_ix, l_ix in zip(poly.vertices, poly.loop_indices):
                        vertex_map[v_ix].append(l_ix)

                if len(data["vertex_color"]) > 0:
                    if len(bm.verts) != len(data["vertex_weights"]):
                        operator.report({'WARNING'}, f"Vertex data mismatched. Contact the author for assistance.")
                        return {'CANCELLED'}
                    for v_ix, l_ixs in vertex_map.items():
                        for l_ix in l_ixs:
                            col.data[l_ix].color = (data["vertex_color"][v_ix][0],data["vertex_color"][v_ix][1],data["vertex_color"][v_ix][2],data["vertex_color"][v_ix][3])
                
                
                if options.meshlets_debug and len(data['meshlets']) > 0:
                    num_meshlets = len(data['meshlets'])

                    for i in range(num_meshlets):
                        material_name = f"Meshlet_{i}"
                        material = bpy.data.materials.new(name=material_name)
                        _h = (0.1 + 0.3*i) % 1.0
                        _s = 1.0
                        _v = 0.8
                        _c = Color()
                        _c.hsv = _h, _s, _v
                        material.diffuse_color = _c[:] + (1.0,)
                        mesh.materials.append(material)


                    for i in range(num_meshlets):
                        tri_counts = data['meshlets'][i][2]
                        tri_offset = data['meshlets'][i][3]
                        for j in range(tri_offset, tri_offset + tri_counts):
                            mesh.polygons[j].material_index = i

                    if options.culldata_debug:
                        
                        for i in range(num_meshlets):
                            center = data['culldata'][i][:3]
                            radius = data['culldata'][i][3]
                            normal = data['culldata'][i][4:7]
                            marker = data['culldata'][i][7]
                            apex = data['culldata'][i][8]

                            bpy.ops.mesh.primitive_uv_sphere_add(radius=radius, location=center)
                            bpy.context.object.display_type = 'BOUNDS'
                            bpy.context.object.display_bounds_type = 'SPHERE'
                            bpy.context.object.show_bounds = True
                            bpy.context.object.name = f"Meshlet_{i}"

                        
                            normal_float = [(_i/255.0)*2 - 1 for _i in normal]
                            is_degenerate = (marker == 255)
                            angle = np.arccos(-marker/255.0) - (3.1415926 / 2)
                            depth = radius / np.tan(angle)
                            cone_center = [_i + _j * depth * 0.5 for _i,_j in zip(center, normal_float)]

                            if not is_degenerate:
                                bpy.ops.mesh.primitive_cone_add(vertices=32, radius1 = radius, depth = depth, location=cone_center)
                                # Calculate the rotation matrix to align the up direction with the normal vector
                                up_vector = mathutils.Vector((0, 0, 1)) 
                                rotation_matrix = up_vector.rotation_difference(mathutils.Vector(normal_float)).to_matrix()

                                # Apply the rotation to the cone
                                bpy.context.object.rotation_euler = rotation_matrix.to_euler()

                                bpy.context.object.display_type = 'BOUNDS'
                                bpy.context.object.display_bounds_type = 'CONE'
                                bpy.context.object.show_bounds = True
                                bpy.context.object.name = f"CullCone_{i}"
                                pass
                            else:

                                pass


                        

            return {'FINISHED'}
        else:
            operator.report({'WARNING'}, f"Unknown error. Contact the author for assistance.")
            return {'CANCELLED'}

    else:
        operator.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
        return {'CANCELLED'}


# Export operator
class ExportCustomMesh(bpy.types.Operator):
    bl_idname = "export.custom_mesh"
    bl_label = "Export Custom Mesh"
    
    filepath: bpy.props.StringProperty(options={'HIDDEN'})
    filename: bpy.props.StringProperty(default='untitled.mesh')
    filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})

    mesh_scale: bpy.props.FloatProperty(
        name="Scale",
        default=1,
    )
    use_world_origin: bpy.props.BoolProperty(
        name="Use world origin",
        description="Use world instead of object origin as output geometry's origin.",
        default=True
    )
    smooth_edge_normals: bpy.props.BoolProperty(
        name="Smooth seam normals",
        description="Average out normals of overlapping vertices",
        default=False,
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
    UV: bpy.props.BoolProperty(
        name="UV",
        description=export_items[2][2],
        default=True
    )
    VERTCOLOR: bpy.props.BoolProperty(
        name="Vertex Color",
        description=export_items[3][2],
        default=True
    )
    WEIGHTS: bpy.props.BoolProperty(
        name="Weights",
        description=export_items[4][2],
        default=True
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
        return ExportMesh(self,context,self.filepath,self)

    def invoke(self, context, event):
        _obj = context.active_object
        if _obj:
            self.filename = _obj.name + '.mesh'
        else:
            self.filename = 'untitled.mesh'
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

# Import operator
class ImportCustomMesh(bpy.types.Operator):
    bl_idname = "import.custom_mesh"
    bl_label = "Import Custom Mesh"
    
    filepath: bpy.props.StringProperty(subtype="FILE_PATH")
    filename: bpy.props.StringProperty(default='untitled.mesh')
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

    def execute(self, context):
        return ImportMesh(self, context, self)

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

class ExportSFMeshOperator(bpy.types.Operator):
    """Export the active object"""
    bl_idname = "export.sfmesh"
    bl_label = "Export Active Mesh"
    
    folder_path: bpy.props.StringProperty(subtype="DIR_PATH", default="")

    def execute(self, context):
        _obj = bpy.context.active_object
        if _obj and _obj.type == 'MESH':
            active_object_name = bpy.context.active_object.name
            return ExportMesh(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, sanitize_filename(active_object_name) + '.mesh'), self)
        
        self.report({'WARNING'}, "You didn't choose a object with geometry!")
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
        layout.prop(context.scene, "use_world_origin", text="Use world origin")
        layout.prop(context.scene, "smooth_edge_normals", text="Smooth seam normals")
        layout.prop(context.scene, "normalize_weights", text="Normalize weights")
        
        
        layout.label(text="Export Datatypes:") 
        # Create a checkbox for each item
        for item in export_items:
            layout.prop(context.scene, item[0], text=item[1])
           
        layout.label(text="After Export:") 
        layout.prop(context.scene, "export_sf_mesh_open_folder", text="Open export folder")
        layout.prop(context.scene, "export_sf_mesh_hash_result", text="Hash file name")
        # Button to export the selected skeleton
        layout.operator("export.sfmesh", text="Export .mesh")


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

# Register the operators and menu entries
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
    bpy.types.Scene.use_world_origin = bpy.props.BoolProperty(
        name="Use world origin",
        description="Use world instead of object origin as output geometry's origin.",
        default=True
    )
    bpy.types.Scene.smooth_edge_normals = bpy.props.BoolProperty(
        name="Smooth seam normals",
        description="Average out normals of overlapping vertices.",
        default=False
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

    bpy.utils.register_class(ExportCustomMesh)
    bpy.utils.register_class(ImportCustomMesh)
    bpy.utils.register_class(ExportSFMeshOperator)
    bpy.utils.register_class(ExportSFMeshPanel)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import)

def unregister():
    bpy.utils.unregister_class(ExportSFMeshOperator)
    bpy.utils.unregister_class(ExportSFMeshPanel)
    bpy.utils.unregister_class(ExportCustomMesh)
    bpy.utils.unregister_class(ImportCustomMesh)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)
    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import)
    del bpy.types.Scene.export_mesh_folder_path
    del bpy.types.Scene.mesh_scale
    del bpy.types.Scene.use_world_origin
    del bpy.types.Scene.smooth_edge_normals
    del bpy.types.Scene.normalize_weights
    del bpy.types.Scene.GEO
    del bpy.types.Scene.NORM
    del bpy.types.Scene.VERTCOLOR
    del bpy.types.Scene.UV
    del bpy.types.Scene.WEIGHTS
    del bpy.types.Scene.export_sf_mesh_open_folder

if __name__ == "__main__":
    register()