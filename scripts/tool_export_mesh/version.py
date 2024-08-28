import addon_utils

class Version:
    def __init__(self, version: tuple[int, int, int] = (0,0,0)):
        self.version = version

    def __str__(self):
        return f"{self.version[0]}.{self.version[1]}.{self.version[2]}"

    def __eq__(self, other):
        return self.version == other.version

    def __lt__(self, other):
        for i in range(3):
            if self.version[i] < other.version[i]:
                return True
        return False

    def __gt__(self, other):
        return not self.__eq__(other) and not self.__lt__(other)

    def __le__(self, other):
        return self.__eq__(other) or self.__lt__(other)

    def __ge__(self, other):
        return self.__eq__(other) or self.__gt__(other)
    
    def as_tuple(self):
        return self.version
    
    def as_str(self):
        return str(self)
    
    def as_int(self):
        return self.version[0] * 10000 + self.version[1] * 100 + self.version[2]
    
def make_version(version: str) -> Version:
    v = Version()
    v.version = tuple(map(int, version.split('.')))
    return v

__extra_compatible_dict__ = {
    (1, 4, 0): {'tool_physics_editor': [(0, 17, 0)]},
    (1, 3, 0): {'tool_physics_editor': [(0, 17, 0)]},
    (1, 2, 0): {'tool_physics_editor': [(0, 17, 0)]},
    (1, 1, 0): {'tool_physics_editor': [(0, 17, 0)]},
    (1, 0, 0): {'tool_physics_editor': [(0, 17, 0)]},
}

def check_compatibility(submodule_name: str, raise_if_not_found: bool = False) -> bool:
    main_name = 'tool_export_mesh'
    _, enabled = addon_utils.check(main_name)
    if not enabled:
        if raise_if_not_found:
            raise Exception(f"Main module '{main_name}' not enabled.")
        return False

    _, enabled = addon_utils.check(submodule_name)
    if not enabled:
        if raise_if_not_found:
            raise Exception(f"Submodule '{submodule_name}' not enabled.")
        return False
    
    mods = addon_utils.modules()
    submodule_version = None
    for mod in mods:
        if mod.__name__ == main_name:
            main_plugin_version = Version(mod.bl_info['version'])
        elif mod.__name__ == submodule_name:
            submodule_version = Version(mod.bl_info['version'])

    return compare_versions(main_plugin_version.as_str(), submodule_version.as_str(), submodule_name)
        
import functools

@functools.lru_cache(maxsize=16)
def compare_versions(main_version_str: str, sub_module_version_str: str, sub_module_name: str) -> bool:
    '''
        return True if the sub_module_version is compatible with the main_version
    '''
    main_version = make_version(main_version_str).as_tuple()
    sub_module_version = make_version(sub_module_version_str).as_tuple()

    #if sub_module_version == main_version:
    #    return True

    if main_version in __extra_compatible_dict__:
        extra_compatible_versions = __extra_compatible_dict__[main_version]
        if sub_module_name in extra_compatible_versions:
            return sub_module_version in extra_compatible_versions[sub_module_name]
        
    return False
        

__plugin_version__ = Version((0, 1, 0))