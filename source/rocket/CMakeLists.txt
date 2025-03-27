#----------------------------------------------------------------------------------------------------------------------
# Simulation executable target
#----------------------------------------------------------------------------------------------------------------------
add_executable(SimulateRocket
        "rocket_sim_csv_data.cpp")

target_compile_options(SimulateRocket
        PRIVATE
        ${CompileOptionsGccExhaustive})

target_include_directories(SimulateRocket
        PRIVATE
        "${CMAKE_SOURCE_DIR}/source/")

#----------------------------------------------------------------------------------------------------------------------
# Real-time thread executable target
#----------------------------------------------------------------------------------------------------------------------
add_executable(RocketSimThread
        "rocket_real_time_thread.cpp")

target_compile_options(RocketSimThread
        PRIVATE
        ${CompileOptionsGccExhaustive})
        
target_include_directories(RocketSimThread
        PRIVATE
        "${CMAKE_SOURCE_DIR}/source/")

#----------------------------------------------------------------------------------------------------------------------
# TCP socket server executable target
#----------------------------------------------------------------------------------------------------------------------
add_executable(RocketSocketServer
        "rocket_sim_tcp_socket_server.cpp")

target_compile_options(RocketSocketServer
        PRIVATE
        ${CompileOptionsGccExhaustive})

target_include_directories(RocketSocketServer
        PRIVATE
        "${CMAKE_SOURCE_DIR}/source/")

 target_link_libraries(RocketSocketServer
        PRIVATE
        "Ws2_32")

#----------------------------------------------------------------------------------------------------------------------
# Unit test target
#----------------------------------------------------------------------------------------------------------------------
add_executable(TestRocket
        "unit_test/test_rocket.cpp")

target_compile_options(TestRocket
        PRIVATE
        ${CompileOptionsGccExhaustive}
        "-Wno-multiple-inheritance")

target_include_directories(TestRocket
        PRIVATE
        "${CMAKE_SOURCE_DIR}/source/")

target_link_libraries(TestRocket
        PRIVATE
        "Catch2::Catch2WithMain")

catch_discover_tests(TestRocket)
