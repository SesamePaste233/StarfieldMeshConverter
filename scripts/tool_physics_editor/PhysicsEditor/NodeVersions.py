import version

__node_versions__: dict[str:tuple[int, int, int]] = {
    'hclLinksFromMesh': (1,0,1),
    'StandardLinkConstraint': (1,0,1),
    'StretchLinkConstraint': (1,0,1),
    'SimClothData': (1,0,1),
    'hclParticlesFromMesh': (1,0,1),
}

def get_node_script_version(bl_idname: str) -> version.Version:
    if bl_idname in __node_versions__:
        return version.Version(__node_versions__[bl_idname])
    else:
        return version.Version((1,0,0))