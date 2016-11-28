standard_flags = "-L compiler/Parser/debug/ -lParserTest -s EXPORTED_FUNCTIONS=['_interpret','_parse','_format_asm']"
debug_flags = standard_flags + " -g -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1"
release_flags = standard_flags + " -O3"
wasm_flags = "-s BINARYEN_METHOD='native-wasm'"

build:
    cargo rustc --release --target asmjs-unknown-emscripten -- -C link-args="{{release_flags}}"
    @cp target/asmjs-unknown-emscripten/release/*.js* docs/.

debug:
    cd compiler && make && cd ..
    cargo rustc --target asmjs-unknown-emscripten -- -C link-args="{{debug_flags}}"
    @cp target/asmjs-unknown-emscripten/debug/*.js* docs/.