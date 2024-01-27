import version

__node_versions__ = {
}

def get_node_version(bl_idname: str):
    if bl_idname in __node_versions__:
        return version.Version(__node_versions__[bl_idname])
    else:
        return version.Version((1,0,0))