set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2)

set(SOURCE srcs/*.c)
add_subdirectory(libft)

add_executable(RT ${SOURCE})
target_link_libraries(RT SDL2::SDL2)
add_dependencies(RT rt_rs libft)  