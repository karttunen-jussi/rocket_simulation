add_executable("SineWaveCsvData"
        sine_wave_csv_data.cpp)

target_compile_options("SineWaveCsvData"
        PRIVATE
        ${CompileOptionsGccExhaustive})
