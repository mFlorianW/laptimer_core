include(Catch)

find_package(Qt5 REQUIRED COMPONENTS Network)

add_executable(test_RequestBuilder test_RequestBuilder.cpp)
target_link_libraries(test_RequestBuilder PRIVATE Qt5::Network Catch2::Catch2 LaptimerCore::SessionDlObj LaptimerCore::RestQt)

catch_discover_tests(test_RequestBuilder)
