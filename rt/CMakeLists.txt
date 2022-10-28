project(RT C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2)

set(SOURCE
    srcs/anti_aliasing_2.c
    srcs/anti_aliasing.c
    srcs/camera.c
    srcs/cartoon_2.c
    srcs/cartoon.c
    srcs/cartoon_seq.c
    srcs/draw_2.c
    srcs/draw.c
    srcs/generate.c
    srcs/interface.c
    srcs/intersection.c
    srcs/light.c
    srcs/main.c
    srcs/object_colors_2.c
    srcs/object_colors.c
    srcs/objects.c
    srcs/perlin.c
    srcs/progess.c
    srcs/read.c
    srcs/reflection.c
    srcs/refraction.c
    srcs/sequence_2.c
    srcs/sequence.c
    srcs/texture_2.c
    srcs/texture.c
    srcs/threads.c
)

    include_directories(includes/)

add_executable(RT ${SOURCE})
add_dependencies(RT rt_rs ft)  
target_link_libraries(RT SDL2::SDL2 m ft)