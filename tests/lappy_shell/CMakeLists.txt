include(Catch)

set(CONFIG_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(test_FilePath.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/FilePath.hpp)

add_executable(test_ApplicationConfigReader test_ApplicationConfigReader.cpp)
target_link_libraries(test_ApplicationConfigReader PRIVATE Catch2::Catch2 LaptimerCore::LappyShellObj)
target_include_directories(test_ApplicationConfigReader PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_ApplicationVersion test_ApplicationVersion.cpp)
target_link_libraries(test_ApplicationVersion PRIVATE Catch2::Catch2 LaptimerCore::LappyShellObj)

catch_discover_tests(test_ApplicationConfigReader)
catch_discover_tests(test_ApplicationVersion)
