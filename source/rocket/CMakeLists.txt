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
# Simulation executable target
#----------------------------------------------------------------------------------------------------------------------
set(SimExecutableName "SimulateRocket")

add_executable(${SimExecutableName}
        rocket_sim_csv_data.cpp)

target_compile_options(${SimExecutableName}
        PRIVATE
        ${CompileOptionsGccExhaustive})

#----------------------------------------------------------------------------------------------------------------------
# Real-time thread executable target
#----------------------------------------------------------------------------------------------------------------------
set(ThreadExecutableName "ExecuteRocketThread")

add_executable(${ThreadExecutableName}
        rocket_real_time_thread.cpp)

target_compile_options(${ThreadExecutableName}
        PRIVATE
        ${CompileOptionsGccExhaustive})