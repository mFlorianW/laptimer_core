include(Catch)

add_executable(test_DeviceModel test_DeviceModel.cpp)
target_link_libraries(test_DeviceModel PRIVATE Catch2::Catch2 Catch2::Catch2WithMain LaptimerCore::LappyShellSettings)

catch_discover_tests(test_DeviceModel)
