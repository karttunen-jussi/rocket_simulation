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
add_executable("SimulateRocket"
        rocket_sim_csv_data.cpp)

target_compile_options("SimulateRocket"
        PRIVATE
        ${CompileOptionsGccExhaustive})

#----------------------------------------------------------------------------------------------------------------------
# Real-time thread executable target
#----------------------------------------------------------------------------------------------------------------------
add_executable("RocketSimThread"
        rocket_real_time_thread.cpp)

target_compile_options("RocketSimThread"
        PRIVATE
        ${CompileOptionsGccExhaustive})

#----------------------------------------------------------------------------------------------------------------------
# TCP socket server executable target
#----------------------------------------------------------------------------------------------------------------------
add_executable("RocketSocketServer"
        rocket_sim_tcp_socket_server.cpp)

target_compile_options("RocketSocketServer"
        PRIVATE
        ${CompileOptionsGccExhaustive})

 target_link_libraries("RocketSocketServer"
        PRIVATE
        Ws2_32)
        