include(Catch)

add_executable(test_GpsEndpoint test_GpsEndpoint.cpp)
target_link_libraries(test_GpsEndpoint PRIVATE Catch2::Catch2 LaptimerCore::Rest)

add_executable(test_Path test_Path.cpp)
target_link_libraries(test_Path PRIVATE Catch2::Catch2 LaptimerCore::Rest)

add_executable(test_SessionEndpoint test_SessionEndpoint.cpp)
target_link_libraries(test_SessionEndpoint PRIVATE Catch2::Catch2 LaptimerCore::TestHelper LaptimerCore::Rest)

catch_discover_tests(test_GpsEndpoint)
catch_discover_tests(test_Path)
catch_discover_tests(test_SessionEndpoint)
