#----------------------------------------------------------------------------------------------------------------------
# Unit test target
#----------------------------------------------------------------------------------------------------------------------
set(TestName "TestRocket")

add_executable(${TestName}
        test_rocket.cpp)

set("CompileOptionsNotWithCatch2"
        -Wno-multiple-inheritance)

target_compile_options(${TestName}
        PRIVATE
        ${CompileOptionsGccExhaustive}
        ${CompileOptionsNotWithCatch2})

target_link_libraries(${TestName}
        PRIVATE
        Catch2::Catch2WithMain)

#----------------------------------------------------------------------------------------------------------------------
# Executable target
#----------------------------------------------------------------------------------------------------------------------
set(ExecutableName "SimulateRocket")

add_executable(${ExecutableName}
        rocket_sim_csv_data.cpp)

target_compile_options(${ExecutableName}
        PRIVATE
        ${CompileOptionsGccExhaustive})