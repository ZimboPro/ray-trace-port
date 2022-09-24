if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD cargo build)
    set(TARGET_DIR "debug")
else ()
    set(CARGO_CMD cargo build --release)
    set(TARGET_DIR "release")
endif ()

set(CLIENT_SO "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_DIR}/librt_rs.so")

add_custom_target(rt_rs ALL
    COMMENT "Compiling client module"
    COMMAND CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} ${CARGO_CMD} 
    COMMAND cp ${CLIENT_SO} ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(rt_rs PROPERTIES LOCATION ${CMAKE_CURRENT_BINARY_DIR})