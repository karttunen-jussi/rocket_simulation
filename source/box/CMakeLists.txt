set(TestName "TestBox")

add_executable(${TestName}
        test_box.cpp)

target_link_libraries(${TestName}
        PRIVATE Catch2::Catch2WithMain)
