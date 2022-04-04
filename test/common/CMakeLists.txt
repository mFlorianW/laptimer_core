include(Catch)

add_executable(test_SharedDataPointer test_SharedDataPointer.cpp)
target_link_libraries(test_SharedDataPointer PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_LapData test_LapData.cpp)
target_link_libraries(test_LapData PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_Timestamp test_Timestamp.cpp)
target_link_libraries(test_Timestamp PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_PositionData test_PositionData.cpp)
target_link_libraries(test_PositionData PRIVATE Catch2::Catch2 LaptimerCore::Common LaptimerCore::TestDummy)

add_executable(test_TrackData test_TrackData.cpp)
target_link_libraries(test_TrackData PRIVATE Catch2::Catch2 LaptimerCore::Common LaptimerCore::TestDummy)

add_executable(test_Date test_Date.cpp)
target_link_libraries(test_Date PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_SessionData test_SessionData.cpp)
target_link_libraries(test_SessionData PRIVATE Catch2::Catch2 LaptimerCore::Common LaptimerCore::TestDummy)

catch_discover_tests(test_SharedDataPointer)
catch_discover_tests(test_LapData)
catch_discover_tests(test_Timestamp)
catch_discover_tests(test_PositionData)
catch_discover_tests(test_TrackData)
catch_discover_tests(test_Date)
catch_discover_tests(test_SessionData)
