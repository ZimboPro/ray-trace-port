# C to Rust Ray Tracing Port

This is an old Ray Tracing project I did in C. The plan is to migrate it step-by-step to Rust.

The reason is mainly to see how it runs in Rust and also to learn about binding from one language to another.

## Progress

The C code has been ported to Rust but it is working correctly.

## Things I Learnt or Wish I had done differently

 * It is recommended to write unit tests for the functions. This will help ensure that the same values will produce the same results in both code bases.
 * Some of the crates(packages/libraries) in Rust are more difficult to automatically generate the structs neededin C. It might be the cbindgen dependency not working as expected or that it was configured incorrectly.
 * Keeping a copy of the unedited code in the repo will make it easier to refer to certain functions before being ported. It could also be used to write unit tests purely for the original code. And those tests can then also be ported over to Rust to ensure that the functions in both code bases return the same values.
