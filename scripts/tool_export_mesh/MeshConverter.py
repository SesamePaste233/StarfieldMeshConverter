import ctypes
import os

# Load the DLL
_dll = ctypes.CDLL(os.path.join(os.path.dirname(__file__),'MeshConverter.dll'))
print("Loaded DLL from: ", os.path.join(os.path.dirname(__file__),'MeshConverter.dll'))
print(_dll)
# Define the function signature
_dll_export_mesh = _dll.ExportMesh
_dll_export_mesh.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_float, ctypes.c_bool, ctypes.c_bool, ctypes.c_bool]

_dll_export_morph = _dll.ExportMorph
_dll_export_morph.argtypes = [ctypes.c_char_p, ctypes.c_char_p]

_dll_export_empty_morph = _dll.ExportEmptyMorph
_dll_export_empty_morph.argtypes = [ctypes.c_uint32, ctypes.c_char_p]

_dll_export_nif = _dll.CreateNif
_dll_export_nif.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]

_dll_import_nif = _dll.ImportNif
_dll_import_nif.argtypes = [ctypes.c_char_p, ctypes.c_bool, ctypes.c_char_p]
_dll_import_nif.restype = ctypes.c_char_p

_dll_edit_nif_bsgeometries = _dll.EditNifBSGeometries
_dll_edit_nif_bsgeometries.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool]

_dll_import_mesh = _dll.ImportMesh
_dll_import_mesh.argtypes = [ctypes.c_char_p]
_dll_import_mesh.restype = ctypes.c_char_p

_dll_import_morph = _dll.ImportMorph
_dll_import_morph.argtypes = [ctypes.c_char_p]
_dll_import_morph.restype = ctypes.c_char_p

_dll_compose_physics_data = _dll.ComposePhysicsData
_dll_compose_physics_data.argtypes = [ctypes.c_char_p, ctypes.c_uint32, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_bool]


from enum import Enum

class Platform(Enum):
    HCL_PLATFORM_INVALID = 0
    HCL_PLATFORM_WIN32 = 1
    HCL_PLATFORM_X64 = 2
    HCL_PLATFORM_MACPPC = 4
    HCL_PLATFORM_IOS = 8
    HCL_PLATFORM_MAC386 = 16
    HCL_PLATFORM_PS3 = 32
    HCL_PLATFORM_XBOX360 = 64
    HCL_PLATFORM_WII = 128
    HCL_PLATFORM_LRB = 256
    HCL_PLATFORM_LINUX = 512
    HCL_PLATFORM_PSVITA = 1024
    HCL_PLATFORM_ANDROID = 2048
    HCL_PLATFORM_CTR = 4096
    HCL_PLATFORM_WIIU = 8192
    HCL_PLATFORM_PS4 = 16384
    HCL_PLATFORM_XBOXONE = 32768
    HCL_PLATFORM_MAC64 = 65536
    HCL_PLATFORM_NX = 131072
    HCL_PLATFORM_GDK = 262144
    HCL_PLATFORM_COOKER = 524288

class DLLReturnCode():
    def __init__(self, return_code: int):
        self.return_code = return_code

    def __bool__(self):
        return self.return_code == 0
    
    def __int__(self):
        return self.return_code
    
    def __str__(self):
        return self.what()

    def what(self):
        match self.return_code:
            case 0:
                return "Success"
            case 2:
                return "Failed to load mesh from blender"
            case 3:
                return "Failed to save mesh to file"
            case 8:
                return "Failed to load morph from blender"
            case 9:
                return "Failed to save morph to file"
            case 10:
                return "Failed to deserialize json to template"
            case 11:
                return "Failed to convert template to nif"
            case 12:
                return "Failed to save nif to file"
            case 13:
                return "Failed to set transcript path"
            case 14:
                return "Physics data build failed"
            case 15:
                return "Failed to open output file"
            case 16:
                return "Failed to edit nif geometries"
            case _:
                return "Unknown error"

def ExportMeshFromJson(json_data_string: str, output_file: str, max_border: float, smooth_edge_normal: bool, normalize_weights: bool, do_optimization: bool) -> DLLReturnCode:
    rtn = _dll_export_mesh(json_data_string.encode('utf-8'), output_file.encode('utf-8'), max_border, smooth_edge_normal, normalize_weights, do_optimization)
    return DLLReturnCode(rtn)

def ExportMorphFromJson(json_data_string: str, output_file: str) -> DLLReturnCode:
    rtn = _dll_export_morph(json_data_string.encode('utf-8'), output_file.encode('utf-8'))
    return DLLReturnCode(rtn)

def ExportEmptyMorphFromJson(num_vertices: int, output_file: str) -> DLLReturnCode:
    rtn = _dll_export_empty_morph(num_vertices, output_file.encode('utf-8'))
    return DLLReturnCode(rtn)

def EditNifBSGeometries(base_nif_path: str, json_data_string: str, output_file: str, assets_folder: str, edit_mat_path: bool = False) -> DLLReturnCode:
    rtn = _dll_edit_nif_bsgeometries(base_nif_path.encode('utf-8'), json_data_string.encode('utf-8'), output_file.encode('utf-8'), assets_folder.encode('utf-8'), edit_mat_path)
    return DLLReturnCode(rtn)

def ImportMeshAsJson(input_file: str) -> str:
    return _dll_import_mesh(input_file.encode('utf-8')).decode('utf-8')

def ImportMorphAsJson(input_file: str) -> str:
    return _dll_import_morph(input_file.encode('utf-8')).decode('utf-8')

def CreateNifFromJson(json_data_string: str, output_file: str, assets_folder_path: str) -> DLLReturnCode:
    rtn = _dll_export_nif(json_data_string.encode('utf-8'), output_file.encode('utf-8'), assets_folder_path.encode('utf-8'))
    return DLLReturnCode(rtn)

def ImportNifAsJson(input_file: str, export_havok_readable: bool = False, readable_path: str = '') -> str:
    return _dll_import_nif(input_file.encode('utf-8'), export_havok_readable, readable_path.encode('utf-8')).decode('utf-8')

def GetTranscriptPath() -> str:
    return os.path.abspath(os.path.join(os.path.dirname(__file__), 'Assets', 'hkTypeTranscript', 'hkTypeTranscript.json'))

def ComposePhysicsDataFromJson(json_data_string: str, platform: Platform, output_binary_path: str, export_readable: bool = False) -> DLLReturnCode:
    transcript_path = GetTranscriptPath()
    rtn = _dll_compose_physics_data(json_data_string.encode('utf-8'), int(platform.value), transcript_path.encode('utf-8'), output_binary_path.encode('utf-8'), export_readable)
    return DLLReturnCode(rtn)