include_directories(inc)
include_directories(src)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
add_executable(structure_basic src/structure_basic.c)
