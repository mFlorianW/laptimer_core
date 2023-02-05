include(Catch)

add_executable(test_GpsEndpoint test_GpsEndpoint.cpp)
target_link_libraries(test_GpsEndpoint PRIVATE Catch2::Catch2 LaptimerCore::Rest)

catch_discover_tests(test_GpsEndpoint)
