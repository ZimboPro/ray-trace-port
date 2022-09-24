extern crate cbindgen;

use std::env;

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    let mut config: cbindgen::Config = Default::default();
    config.language = cbindgen::Language::C;
    config.no_includes = true;  
    config.include_guard = Some("rt_rs_h".to_string());
    cbindgen::generate_with_config(&crate_dir, config)
      .unwrap()
      .write_to_file("target/rt_rs.h");
}