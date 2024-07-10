import mathutils
from scipy.interpolate import Rbf, RBFInterpolator
import numpy as np
import functools

import bpy

import utils_math

class Transferable:
    def __init__(self) -> None:
        self.positions = []
        self.normals = []
        self.data = []
        self.weights = []
        self.unique_indices_np: np.ndarray = None

    @functools.lru_cache(4)
    def _calc_unique(self):
        positions_np = np.array(self.positions)
        _, unique_indices = np.unique(positions_np, axis=0, return_index=True)
        self.unique_indices = unique_indices
    
    def Unique(self):
        self._calc_unique()

    def AddEmptyData(self, position:mathutils.Vector, normal:mathutils.Vector):
        self.positions.append([position.x, position.y, position.z])
        self.normals.append([normal.x, normal.y, normal.z])
        self.data.append([])

    def AddData(self, position:mathutils.Vector, normal:mathutils.Vector, data:float):
        self.positions.append([position.x, position.y, position.z])
        self.normals.append([normal.x, normal.y, normal.z])
        self.data.append([data])

    def AddListData(self, position:mathutils.Vector, normal:mathutils.Vector, data_list:list):
        self.positions.append([position.x, position.y, position.z])
        self.normals.append([normal.x, normal.y, normal.z])
        self.data.append(data_list)
            
    def SetData(self, new_data):
        self.data = new_data
        if 'DataNumpy' in self.__dict__:
            del self.__dict__['DataNumpy']
        if 'DataMathutils' in self.__dict__:
            del self.__dict__['DataMathutils']

    def ResetCache(self):
        if 'PositionsMathutils' in self.__dict__:
            del self.__dict__['PositionsMathutils']
        if 'DataMathutils' in self.__dict__:
            del self.__dict__['DataMathutils']
        if 'DataNumpy' in self.__dict__:
            del self.__dict__['DataNumpy']
        if 'PositionsNumpy' in self.__dict__:
            del self.__dict__['PositionsNumpy']
        if 'KDTree' in self.__dict__:
            del self.__dict__['KDTree']

    @functools.cached_property
    def PositionsMathutils(self) -> list[mathutils.Vector]:
        return [mathutils.Vector(p) for p in self.positions]

    @functools.cached_property
    def DataMathutils(self) -> list[mathutils.Vector]:
        return [mathutils.Vector(d) for d in self.data]

    @functools.cached_property
    def PositionsNumpy(self) -> np.ndarray:
        return np.array(self.positions)

    def PositionsEnhanced(self, depth:float) -> np.ndarray:
        return self.PositionsNumpy + np.array(self.normals) * depth

    @functools.cached_property
    def DataNumpy(self) -> np.ndarray:
        return np.array(self.data)


    @functools.cached_property
    def KDTree(self):
        kdtree = mathutils.kdtree.KDTree(len(self.positions))
        for i, p in enumerate(self.PositionsMathutils):
            kdtree.insert(p, i)
        kdtree.balance()
            
        return kdtree

    def GenWeightingScheme(self, target, sigma:float = 0.1, additional_BVHTree: mathutils.bvhtree.BVHTree = None):
        if additional_BVHTree is not None:
            distances = [_ for _ in range(len(self.PositionsMathutils))]
            for i, p in enumerate(self.PositionsMathutils):
                bvh_rtn_lst = additional_BVHTree.find_nearest_range(p, 3 * sigma)

                if len(bvh_rtn_lst) == 0:
                    distances[i] = 3 * sigma
                    continue
                
                distances[i] = min([rtn[3] for rtn in bvh_rtn_lst])
            
            distances = np.array(distances)
        else:
            tar_kdtree = target.KDTree
            _, _, distances = GetClosestNPoints(tar_kdtree, self.PositionsMathutils, 3)
            distances = np.array(distances)
            distances = np.sum(distances, axis=1)
            
        # Gaussian falloff
        self.weights = np.exp(-distances**2 / (2 * sigma**2))

        # Set weights to 0 if the distance is too large
        self.weights[distances > 3 * sigma] = 0
    
    def CopyClosest(self, target, closest_range: float = 0.005):
        tar_kdtree = target.KDTree
        _, closest_points, distances = GetClosestNPoints(tar_kdtree, self.PositionsMathutils, 1)
        closest_points = [rtn[0] for rtn in closest_points]
        distances = [rtn[0] for rtn in distances]
        for i in range(len(self.positions)):
            if distances[i] < closest_range:
                self.data[i] = target.data[closest_points[i]]

    def Save(self, path:str):
        np.savez(path, positions=self.positions, data=self.data)

    def Load(self, path:str):
        npzfile = np.load(path)
        self.positions = npzfile['positions']
        self.data = npzfile['data']
        

def GetClosestNPoints(kdtree:mathutils.kdtree.KDTree, points: list[mathutils.Vector], n:int) -> list[list[int]]:
    positions = []
    indices = []
    distances = []
    for p in points:
        rtns = kdtree.find_n(p, n)
        positions.append([rtn[0] for rtn in rtns])
        indices.append([rtn[1] for rtn in rtns])
        distances.append([rtn[2] for rtn in rtns])
    return positions, indices, distances

def RBFTransfer(source: Transferable, target: Transferable, neighbours: int = 15, smoothing = 0, epsilon = None, kernel = 'Gaussian', use_normals = True, surface_depth = 0.1, scale = 1):
    '''
    Radial Basis Function Transfer.
    '''
    inv_scale = 1/scale
    
    positions = source.PositionsNumpy
    if source.unique_indices_np is not None:
        positions = positions[source.unique_indices_np]

    data = source.DataNumpy
    if source.unique_indices_np is not None:
        data = data[source.unique_indices_np]

    if use_normals:
        positions_enhanced = source.PositionsEnhanced(surface_depth)

        positions = np.concatenate((positions, positions_enhanced), axis=0)
        
        data = np.concatenate((data, data), axis=0)

    n_sample = positions.shape[0]

    if neighbours > n_sample:
        neighbours = n_sample

    rbf = RBFInterpolator(positions * scale, data * scale, neighbors=neighbours, epsilon=epsilon, smoothing=smoothing, kernel=kernel)

    if len(target.weights) == len(target.positions):
        weights_larger_than_zero = target.weights > 0

        target_positions = target.PositionsNumpy[weights_larger_than_zero] * scale

        new_data = np.zeros((len(target.positions), data.shape[1]))

        new_data[weights_larger_than_zero] = (rbf(target_positions) * inv_scale)

        target.SetData(new_data.tolist())

    else:
        target_positions = target.PositionsNumpy * scale

        new_data = (rbf(target_positions) * inv_scale)

        target.SetData(new_data.tolist())
    
def IDWTransfer(source: Transferable, target: Transferable, neighbours: int = 15, smoothing = 0, epsilon = None, degrees = 5, kernel = 'Gaussian', use_normals = True, surface_depth = 0.1, scale = 1):
    '''
    Inverse Distance Weighting Transfer.    
    '''
    inv_scale = 1/scale
    if len(source.positions) == 0 or len(target.positions) == 0:
        return

    _, closest_points, _ = GetClosestNPoints(source.KDTree, target.PositionsMathutils, neighbours)

    new_data = [_ for _ in len(target.PositionsMathutils)]
    for i, p in enumerate(target.PositionsMathutils):
        neighbours = closest_points[i]
        neighbours_positions_raw = [source.positions[n] for n in neighbours]
        if use_normals:
            neighbours_positions_enhanced = [np.array(source.positions[n]) + np.array(source.normals[n]) * surface_depth for n in neighbours]
        neighbours_data_raw = [source.data[n] for n in neighbours]

        neighbours_positions = neighbours_positions_raw + neighbours_positions_enhanced
        neighbours_data = neighbours_data_raw + neighbours_data_raw

        np_p = np.array(neighbours_positions)
        np_d = np.array(neighbours_data)

        new_data[i] = idw_interpolation(np_p * scale, np_d * scale, np.array([p])*scale, degrees).flatten()*inv_scale

    target.SetData(new_data)

def idw_interpolation(X: np.ndarray, Y: np.ndarray, x: np.ndarray, p: float) -> np.ndarray:
    '''
    Inverse Distance Weighting Interpolation.
        X: n x d
        Y: n x s
        x: m x d
        p: float
        return: m x s
    '''
    n, d = X.shape
    m, s = Y.shape
    assert d == x.shape[1]

    # Calculate distance matrix
    dist = np.linalg.norm(X[:, np.newaxis] - x, axis=2)
    weights = 1 / dist ** p
    weights /= np.sum(weights, axis=0)

    weights[np.isnan(weights)] = 1


    # Interpolation
    Y_interp = np.sum(weights[:, :, np.newaxis] * Y[:, np.newaxis], axis=0)
    return Y_interp
    

def ShapekeyDataToTransferable(obj:bpy.types.Object, shapekey:bpy.types.ShapeKey, target:Transferable):
    data = []
    for i, v in enumerate(obj.data.vertices):
        data.append(shapekey.data[i].co - v.co)

    target.SetData(data)

def MeshShapeKeyToTransferable(obj:bpy.types.Object, shapekey:bpy.types.ShapeKey):
    target = Transferable()
    for i, v in enumerate(obj.data.vertices):
        target.AddListData(obj.matrix_world @ v.co, v.normal, shapekey.data[i].co - v.co)
    return target

def MeshToTransferable(obj:bpy.types.Object):
    target = Transferable()
    for i, v in enumerate(obj.data.vertices):
        target.AddEmptyData(obj.matrix_world @ v.co, v.normal)
    return target

def TransferableToMeshShapeKey(obj:bpy.types.Object, shapekey:bpy.types.ShapeKey, source:Transferable):
    if len(source.weights) == len(source.positions):
        for i, v, w in zip(range(len(obj.data.vertices)), obj.data.vertices, source.weights):
            if w > 0:
                shapekey.data[i].co = v.co + source.DataMathutils[i] * w
    else:
        for i, v in enumerate(obj.data.vertices):
            shapekey.data[i].co = v.co + source.DataMathutils[i]
        

def TransferShapekeys(source_obj:bpy.types.Object, target_obj:bpy.types.Object, shape_key_name_lst:list[str], falloff_sigma = 0.1, copy_range = 0.005, create_if_not_exist:bool = True, dont_create_if_unobvious:bool = True):
    source = MeshToTransferable(source_obj)
    source.Unique()
    target = MeshToTransferable(target_obj)

    #source_bvh_tree = mathutils.bvhtree.BVHTree.FromObject(source_obj, bpy.context.evaluated_depsgraph_get())

    target.GenWeightingScheme(source, sigma = falloff_sigma)#, additional_BVHTree=source_bvh_tree)

    for shape_key_name in shape_key_name_lst:
        if shape_key_name not in source_obj.data.shape_keys.key_blocks:
            print(f"Shapekey {shape_key_name} not found in source object.")
            continue
        
        source_shapekey = source_obj.data.shape_keys.key_blocks[shape_key_name]

        ShapekeyDataToTransferable(source_obj, source_shapekey, source)

        if shape_key_name not in target_obj.data.shape_keys.key_blocks:
            if create_if_not_exist:
                target_obj.shape_key_add(name=shape_key_name)
            else:
                print(f"Shapekey {shape_key_name} not found in target object.")
                continue

        target_shapekey = target_obj.data.shape_keys.key_blocks[shape_key_name]

        RBFTransfer(source, target, scale = 74, epsilon = 3, neighbours = 8, smoothing = 0, use_normals = False)

        if dont_create_if_unobvious:
            if np.max(np.abs(target.DataNumpy)) < 0.001:
                target_obj.shape_key_remove(target_shapekey)
                print(f"Shapekey {shape_key_name} is unobvious, removed.")
                continue

        if copy_range > 0:
            target.CopyClosest(source, copy_range)

        TransferableToMeshShapeKey(target_obj, target_shapekey, target)

    source.ResetCache()
    target.ResetCache()


if __name__ == "__main__":
    # Example usage, not meant for running
    # Transfer all shapekeys from selected object to active object
    active_obj = bpy.context.active_object

    selected_objs = bpy.context.selected_objects
    selected_obj = [tar for tar in selected_objs if tar != active_obj][0]

    shape_key_name_lst = [sk.name for sk in selected_obj.data.shape_keys.key_blocks if sk.name != "Basis"]

    TransferShapekeys(selected_obj, active_obj, shape_key_name_lst, falloff_sigma=0.15, copy_range=0.005)