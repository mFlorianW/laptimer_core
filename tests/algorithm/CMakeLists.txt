include(Catch)

add_executable(test_TrackDetection test_TrackDetection.cpp)
target_link_libraries(test_TrackDetection PRIVATE Catch2::Catch2 Rapid::AlgorithmObject)

add_executable(test_SimpleLaptimer test_SimpleLaptimer.cpp)
target_link_libraries(test_SimpleLaptimer PRIVATE Catch2::Catch2 Rapid::AlgorithmObject LaptimerCore::TestHelper)

catch_discover_tests(test_TrackDetection)
catch_discover_tests(test_SimpleLaptimer)
