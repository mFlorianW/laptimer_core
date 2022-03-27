include(Catch)

add_executable(test_SharedDataPointer test_SharedDataPointer.cpp)
target_link_libraries(test_SharedDataPointer PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_LapData test_LapData.cpp)
target_link_libraries(test_LapData PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_Timestamp test_Timestamp.cpp)
target_link_libraries(test_Timestamp PRIVATE Catch2::Catch2 LaptimerCore::Common)

catch_discover_tests(test_SharedDataPointer)
catch_discover_tests(test_LapData)
catch_discover_tests(test_Timestamp)
