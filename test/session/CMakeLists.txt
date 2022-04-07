include(Catch)

add_executable(test_SessionDatabase test_SessionDatabase.cpp)
target_link_libraries(test_SessionDatabase PRIVATE Catch2::Catch2 LaptimerCore::Session LaptimerCore::TestDummy)

catch_discover_tests(test_SessionDatabase)
