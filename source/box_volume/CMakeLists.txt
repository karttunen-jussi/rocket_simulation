set(TestName "TestBoxVolume")

add_executable(${TestName}
        test_box_volume.cpp)

target_link_libraries(${TestName}
        PRIVATE Catch2::Catch2WithMain)
