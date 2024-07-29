from scipy.interpolate import Rbf, RBFInterpolator
from scipy.spatial import cKDTree
import numpy as np
import functools

import bpy

import utils_math

from utils_common import timer

from time import time

class Transferable:
    def __init__(self) -> None:
        self.positions: np.ndarray = None
        self.normals: np.ndarray = None
        self.data: np.ndarray = None
        self.weights: np.ndarray = None
        self.unique_indices_np: np.ndarray = None

    @functools.lru_cache(4)
    def _calc_unique(self):
        positions_np = np.array(self.positions)
        _, unique_indices = np.unique(positions_np, axis=0, return_index=True)
        self.unique_indices_np = unique_indices
    
    def Unique(self):
        self._calc_unique()
            
    def SetData(self, new_data):
        self.data = new_data

    def ResetCache(self):
        if 'KDTree' in self.__dict__:
            del self.__dict__['KDTree']

    def PositionsEnhanced(self, depth:float) -> np.ndarray:
        return self.positions + np.array(self.normals) * depth

    @functools.cached_property
    def KDTree(self) -> cKDTree:
        return cKDTree(self.positions)

    @timer
    def GenWeightingScheme(self, target, sigma:float = 0.1, copy_range = 0.005):
        tar_kdtree: cKDTree = target.KDTree
        _, _, distances = GetClosestNPoints(tar_kdtree, self.positions, 1)
        
        distances = distances - copy_range
        distances[distances < 0] = 0

        # Gaussian falloff
        self.weights = np.exp(-distances**2 / (2 * sigma**2))

        # Set weights to 0 if the distance is too large
        self.weights[distances > 3 * sigma] = 0
    
    @timer
    def CopyClosest(self, target, closest_range: float = 0.005):
        tar_kdtree: cKDTree = target.KDTree

        dists, indices = tar_kdtree.query(self.positions, k=1)
        mask = dists < closest_range
        indices = indices[mask]

        self.data[mask] = target.data[indices]

    def Save(self, path:str):
        np.savez(path, positions=self.positions, data=self.data)

    def Load(self, path:str):
        npzfile = np.load(path)
        self.positions = npzfile['positions']
        self.data = npzfile['data']
    
    def check_consistency(self) -> bool:
        return len(self.positions) == len(self.data)

def GetClosestNPoints(kdtree:cKDTree, points: np.ndarray, n:int) -> list[list[int]]:
    dists, indices = kdtree.query(points, k=n)
    return kdtree.data[indices], indices, dists

@timer
def RBFTransfer(source: Transferable, target: Transferable, neighbours: int = 15, smoothing = 0, epsilon = None, kernel = 'Gaussian', use_normals = True, surface_depth = 0.1, scale = 1):
    '''
    Radial Basis Function Transfer.
    '''
    t1 = time()
    inv_scale = 1/scale
    
    positions = source.positions
    if source.unique_indices_np is not None:
        positions = positions[source.unique_indices_np]

    data = source.data
    if source.unique_indices_np is not None:
        data = data[source.unique_indices_np]

    if use_normals:
        positions_enhanced = source.PositionsEnhanced(surface_depth)

        positions = np.concatenate((positions, positions_enhanced), axis=0)
        
        data = np.concatenate((data, data), axis=0)

    n_sample = positions.shape[0]

    if neighbours > n_sample:
        neighbours = n_sample

    t2 = time()
    print(f"Preparation time: {t2 - t1}")

    rbf = RBFInterpolator(positions * scale, data * scale, neighbors=neighbours, epsilon=epsilon, smoothing=smoothing, kernel=kernel)

    if target.weights is not None and len(target.weights) == len(target.positions):
        weights_larger_than_zero = target.weights > 0

        target_positions = target.positions[weights_larger_than_zero] * scale

        new_data = np.zeros((len(target.positions), data.shape[1]))

        new_data[weights_larger_than_zero] = (rbf(target_positions) * inv_scale)

        target.SetData(new_data)

    else:
        target_positions = target.positions * scale

        new_data = (rbf(target_positions) * inv_scale)

        target.SetData(new_data)

    t3 = time()
    print(f"RBFInterpolator time: {t3 - t2}")

    
def IDWTransfer(source: Transferable, target: Transferable, neighbours: int = 15, smoothing = 0, epsilon = None, degrees = 5, kernel = 'Gaussian', use_normals = True, surface_depth = 0.1, scale = 1):
    '''
    Inverse Distance Weighting Transfer.    
    '''
    inv_scale = 1/scale
    if len(source.positions) == 0 or len(target.positions) == 0:
        return

    _, closest_points, _ = GetClosestNPoints(source.KDTree, target.positions, neighbours)

    new_data = [_ for _ in len(target.positions)]
    for i, p in enumerate(target.positions):
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


@timer
def MeshToTransferable(obj:bpy.types.Object):
    target = Transferable()
    pos = np.empty((len(obj.data.vertices), 3), dtype=np.float32)
    obj.data.vertices.foreach_get('co', pos.ravel())
    pos = utils_math.apply_mat_to_all(obj.matrix_world, pos)

    norm = np.empty((len(obj.data.vertices), 3), dtype=np.float32)
    obj.data.vertices.foreach_get('normal', norm.ravel())

    normal_transform = obj.matrix_world.to_3x3().inverted_safe().transposed()
    norm = utils_math.apply_mat_to_all(normal_transform, norm)

    target.positions = pos
    target.normals = norm
    return target


@timer
def ShapekeyDataToTransferable(obj:bpy.types.Object, shapekey:bpy.types.ShapeKey, target:Transferable):
    size = (len(obj.data.vertices), 3)
    target_pos = np.empty(size, dtype=np.float32)
    basis_pos = np.empty(size, dtype=np.float32)
    rot_transform = np.array(obj.matrix_world.to_3x3())
    obj.data.vertices.foreach_get('co', basis_pos.ravel())
    shapekey.data.foreach_get('co', target_pos.ravel())
    target.SetData((target_pos - basis_pos) @ rot_transform.T)


@timer
def TransferableToMeshShapeKey(obj:bpy.types.Object, shapekey:bpy.types.ShapeKey, source:Transferable):
    basis_pos = np.empty((len(obj.data.vertices), 3), dtype=np.float32)
    obj.data.vertices.foreach_get('co', basis_pos.ravel())

    rot_transform = np.array(obj.matrix_world.to_3x3())
    if source.weights is not None and len(source.weights) == len(source.positions):
        target_data = basis_pos + source.data @ rot_transform * source.weights[:, np.newaxis]
    else:
        target_data = basis_pos + source.data @ rot_transform

    shapekey.data.foreach_set('co', target_data.ravel())
        

@timer
def TransferShapekeys(source_obj:bpy.types.Object, target_obj:bpy.types.Object, shape_key_name_lst:list[str], falloff_sigma = 0.1, copy_range = 0.005, create_if_not_exist:bool = True, dont_create_if_unobvious:bool = True):
    source = MeshToTransferable(source_obj)
    source.Unique()
    target = MeshToTransferable(target_obj)

    #source_bvh_tree = mathutils.bvhtree.BVHTree.FromObject(source_obj, bpy.context.evaluated_depsgraph_get())

    target.GenWeightingScheme(source, sigma = falloff_sigma, copy_range = copy_range)#, additional_BVHTree=source_bvh_tree)

    for shape_key_name in shape_key_name_lst:
        if shape_key_name not in source_obj.data.shape_keys.key_blocks:
            print(f"Shapekey {shape_key_name} not found in source object.")
            continue
        
        source_shapekey = source_obj.data.shape_keys.key_blocks[shape_key_name]

        ShapekeyDataToTransferable(source_obj, source_shapekey, source)

        if target_obj.data.shape_keys is None:
            target_obj.shape_key_add(name="Basis")

        if shape_key_name not in target_obj.data.shape_keys.key_blocks:
            if create_if_not_exist:
                target_obj.shape_key_add(name=shape_key_name)
            else:
                print(f"Shapekey {shape_key_name} not found in target object.")
                continue

        target_shapekey = target_obj.data.shape_keys.key_blocks[shape_key_name]

        RBFTransfer(source, target, scale = 74, epsilon = 3, neighbours = 8, smoothing = 0, use_normals = False)

        if dont_create_if_unobvious:
            if np.max(np.abs(target.data)) < 0.001:
                target_obj.shape_key_remove(target_shapekey)
                print(f"Shapekey {shape_key_name} is unobvious, removed.")
                continue

        if copy_range > 0:
            target.CopyClosest(source, copy_range)

        TransferableToMeshShapeKey(target_obj, target_shapekey, target)
        print(f"Shapekey {shape_key_name} transferred.")


if __name__ == "__main__":
    # Example usage, not meant for running
    # Transfer all shapekeys from selected object to active object
    active_obj = bpy.context.active_object

    selected_objs = bpy.context.selected_objects
    selected_obj = [tar for tar in selected_objs if tar != active_obj][0]

    shape_key_name_lst = [sk.name for sk in selected_obj.data.shape_keys.key_blocks if sk.name != "Basis"]

    TransferShapekeys(selected_obj, active_obj, shape_key_name_lst, falloff_sigma=0.15, copy_range=0.005)