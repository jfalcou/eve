__copyright__ = "EVE Project Contributors"
__license__   = "BSL-1.0"

# Every include rule for eve. Paths are include paths, as written in #include <...>.

# Outside of the folder, only its entry header may be included.
PRIVATE_FOLDERS = {
  'eve/config': 'eve/config.hpp',
}

# Files of the folder, including its entry header, may only include the folder itself and these eve
# headers. A path ending with '/' allows a whole folder.
LAYERS = {
  'eve/config': ['eve/deps/spy.hpp'],
}

# These headers may only be included from files of the folder.
INCLUDED_ONLY_FROM = {
  'eve/deps/spy.hpp': 'eve/config',
}
