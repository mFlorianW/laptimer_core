include(Catch)

add_executable(test_Timer test_Timer.cpp)
target_link_libraries(test_Timer PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_FutureWatcher test_FutureWatcher.cpp)
target_link_libraries(test_FutureWatcher PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_SignalDispatcher test_SignalDispatcher.cpp)
target_link_libraries(test_SignalDispatcher PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_AsyncResult test_AsyncResult.cpp)
target_link_libraries(test_AsyncResult PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_Event test_Event.cpp)
target_link_libraries(test_Event PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_EventLoop test_EventLoop.cpp)
target_link_libraries(test_EventLoop PRIVATE Catch2::Catch2 LaptimerCore::System)


catch_discover_tests(test_Timer)
catch_discover_tests(test_FutureWatcher)
catch_discover_tests(test_SignalDispatcher)
catch_discover_tests(test_AsyncResult)
catch_discover_tests(test_Event)
catch_discover_tests(test_EventLoop)
