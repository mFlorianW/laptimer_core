include(Catch)

add_executable(test_RestGpsSource test_RestGpsSource.cpp)
target_link_libraries(test_RestGpsSource PRIVATE Catch2::Catch2 LaptimerCore::Rest)

catch_discover_tests(test_RestGpsSource)
