extern crate cbindgen;

use std::env;

use cbindgen::{ItemType, StructConfig};

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    let mut config: cbindgen::Config = Default::default();
    config.language = cbindgen::Language::C;
    config.no_includes = true;
    config.structure = StructConfig {
        derive_constructor: true,
        ..Default::default()
    };
    config.export.item_types = [
        ItemType::Enums,
        ItemType::Structs,
        ItemType::Functions,
        ItemType::Typedefs,
        ItemType::Unions,
        ItemType::OpaqueItems,
        ItemType::Globals,
    ]
    .to_vec();
    config.export.include = ["SDL_Color".to_string(), "ObjectType".to_string(), "WorldObject".to_string()].to_vec();
    config.after_includes = Some("# include <SDL2/SDL.h>".to_string());
    // config.parse.extra_bindings = ["sdl2".to_string()].to_vec();
    config.parse.parse_deps = true;
    // config.parse.include = Some(["sdl2".to_string()].to_vec());
    config.style.generate_typedef();
    config.parse.exclude = ["cbindgen".to_string(), "libc".to_string()].to_vec();
    config.include_guard = Some("rt_rs_h".to_string());
    cbindgen::generate_with_config(&crate_dir, config)
        .unwrap()
        .write_to_file("target/rt_rs.h");
}
