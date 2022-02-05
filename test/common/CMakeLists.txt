include(Catch)

add_executable(test_SharedDataPointer test_SharedDataPointer.cpp)
target_link_libraries(test_SharedDataPointer PRIVATE Catch2::Catch2 LaptimerCore::Common)

catch_discover_tests(test_SharedDataPointer)