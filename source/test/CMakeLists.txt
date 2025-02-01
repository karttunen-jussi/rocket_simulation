set(TestName "UnitTestExample")

add_executable(${TestName}
        test_example.cpp)

target_link_libraries(${TestName}
        PRIVATE Catch2::Catch2WithMain)
