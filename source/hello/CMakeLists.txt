add_executable("HelloWorld"
        hello_world.cpp)

target_compile_options("HelloWorld"
        PRIVATE
        ${CompileOptionsGccExhaustive})
