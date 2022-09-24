include(FetchContent)

FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
    GIT_TAG v0.2.1 # Optionally specify a commit hash, version tag or branch here
)

FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH Cargo.toml)

target_include_directories(rt_rs
    INTERFACE
    target/
    )

# # Wrapper for bindgen
# target_sources(rt_rs
#     INTERFACE
#     target/rt_rs.h
#     )

# target_link_libraries(rt_rs
#     INTERFACE
#     c_lib
#     )