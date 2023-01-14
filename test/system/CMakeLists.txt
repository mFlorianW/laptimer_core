include(Catch)

add_executable(test_Timer test_Timer.cpp)
target_link_libraries(test_Timer PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_FutureWatcher test_FutureWatcher.cpp)
target_link_libraries(test_FutureWatcher PRIVATE Catch2::Catch2 LaptimerCore::System)

catch_discover_tests(test_Timer)
