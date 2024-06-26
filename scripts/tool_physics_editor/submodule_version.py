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

import addon_utils
import os
import sys

main_module_name = 'tool_export_mesh'
mods = addon_utils.modules()

path = None
compare_versions = lambda main_version_str, sub_module_version_str, sub_module_name: False
check_compatibility = lambda submodule_name, raise_if_not_found = False: False

for mod in mods:
    if mod.__name__ == main_module_name:
        path = os.path.dirname(mod.__file__)
        
if path:
    sys.path.append(os.path.abspath(path))
    
    import version
    compare_versions = version.compare_versions
    check_compatibility = version.check_compatibility

__plugin_version__ = Version((0, 1, 0))