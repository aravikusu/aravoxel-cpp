cmake_minimum_required(VERSION 3.5.0)
project(aravoxel VERSION 0.1.0 LANGUAGES C CXX)

file (GLOB_RECURSE aravoxel_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE aravoxel_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (aravoxel_INCLUDE_DIRS "")
foreach (_headerFile ${aravoxel_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND aravoxel_INCLUDE_DIRS ${_dir})
endforeach()
list (APPEND aravoxel_INCLUDE_DIRS include/)
list (REMOVE_DUPLICATES aravoxel_INCLUDE_DIRS)

add_executable(aravoxel ${aravoxel_SOURCES} src/glad.c)

target_include_directories(aravoxel PRIVATE ${aravoxel_INCLUDE_DIRS})

target_link_libraries(aravoxel glfw3 GL X11 pthread Xrandr Xi dl)