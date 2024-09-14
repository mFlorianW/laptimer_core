include(Catch)

add_executable(test_Timer test_Timer.cpp)
target_link_libraries(test_Timer PRIVATE Catch2::Catch2 LaptimerCore::System LaptimerCore::TestHelper)

add_executable(test_FutureWatcher test_FutureWatcher.cpp)
target_link_libraries(test_FutureWatcher PRIVATE Catch2::Catch2 LaptimerCore::System LaptimerCore::TestHelper)

add_executable(test_AsyncResult test_AsyncResult.cpp)
target_link_libraries(test_AsyncResult PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_Event test_Event.cpp)
target_link_libraries(test_Event PRIVATE Catch2::Catch2 LaptimerCore::System)

add_executable(test_EventLoop test_EventLoop.cpp)
target_link_libraries(test_EventLoop PRIVATE Catch2::Catch2 LaptimerCore::System)

catch_discover_tests(test_Timer)
catch_discover_tests(test_FutureWatcher)
catch_discover_tests(test_AsyncResult)
catch_discover_tests(test_Event)
catch_discover_tests(test_EventLoop)

if(ENABLE_QT)
    ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    find_package(Qt5Test REQUIRED)

    add_executable(test_QEventDispatcher test_QEventDispatcher.cpp)
    target_link_libraries(test_QEventDispatcher PRIVATE Qt5::Test LaptimerCore::SystemQt)
endif()
