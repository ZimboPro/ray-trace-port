project(RT C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2)
Include(FetchContent)

FetchContent_Declare(
  check
  GIT_REPOSITORY https://github.com/libcheck/check.git
  GIT_TAG        0.15.2 # or a later release
)

FetchContent_MakeAvailable(check)

set(SOURCE
srcs/anti_aliasing_2.c
srcs/anti_aliasing.c
srcs/cal.c
srcs/calc_1.c
srcs/calc_2.c
srcs/calc.c
srcs/camera_2.c
srcs/camera.c
srcs/cartoon_2.c
srcs/cartoon.c
srcs/cartoon_seq.c
srcs/check_2.c
srcs/check.c
srcs/cone_2.c
srcs/cone.c
srcs/cylinder_2.c
srcs/cylinder.c
srcs/draw_2.c
srcs/draw.c
srcs/generate.c
srcs/interface.c
srcs/intersection.c
srcs/light.c
srcs/normal.c
srcs/object_colors_2.c
srcs/object_colors.c
srcs/objects.c
srcs/perlin.c
srcs/plane.c
srcs/progess.c
srcs/read.c
srcs/reflection.c
srcs/refraction.c
srcs/rotation.c
srcs/scale.c
srcs/sequence_2.c
srcs/sequence.c
srcs/sphere_2.c
srcs/sphere.c
srcs/texture_2.c
srcs/texture.c
srcs/threads.c
srcs/translation.c
)

include_directories(includes/)
add_library(rtlib STATIC ${SOURCE})

add_executable(RT_ORIG srcs/main.c )
add_executable(rt_tests tests/test.c )
add_dependencies(RT_ORIG ft)  
target_link_libraries(RT_ORIG rtlib SDL2::SDL2 m ft)
target_link_libraries(rt_tests rtlib SDL2::SDL2 m ft check)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
# include(Catch)
# catch_discover_tests(rt_tests)