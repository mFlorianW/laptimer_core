include(Catch)

add_executable(test_TrackDetection test_TrackDetection.cpp)
target_link_libraries(test_TrackDetection PRIVATE Catch2::Catch2 LaptimerCore::AlgorithmObject)

catch_discover_tests(test_TrackDetection)