include(Catch)

set(CONFIG_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CONFIG_APP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/testapps)
configure_file(test_FilePath.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/FilePath.hpp)

set(DUMMY_PROCESS_BINARY_PATH ${CMAKE_CURRENT_BINARY_DIR}/dummy_process)
set(DUMMY_PROCESS_BINARY_NAME "dummy_process")
configure_file(DummyProcessPath.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/DummyProcessPath.hpp)


add_executable(test_ApplicationConfigReader test_ApplicationConfigReader.cpp)
target_link_libraries(test_ApplicationConfigReader PRIVATE Catch2::Catch2 LaptimerCore::LappyShellApplications)
target_include_directories(test_ApplicationConfigReader PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_ApplicationVersion test_ApplicationVersion.cpp)
target_link_libraries(test_ApplicationVersion PRIVATE Catch2::Catch2 LaptimerCore::LappyShellApplications)

add_executable(test_ApplicationModel test_ApplicationModel.cpp)
target_link_libraries(test_ApplicationModel PRIVATE Catch2::Catch2 LaptimerCore::LappyShellApplications)
target_include_directories(test_ApplicationModel PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_ApplicationListModel test_ApplicationListModel.cpp)
target_link_libraries(test_ApplicationListModel PRIVATE Catch2::Catch2 Catch2::Catch2WithMain LaptimerCore::LappyShellApplications Qt6::Test)
target_include_directories(test_ApplicationListModel PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_GlobalSettingsWriter test_GlobalSettingsWriter.cpp)
target_link_libraries(test_GlobalSettingsWriter PRIVATE Catch2::Catch2 Catch2::Catch2WithMain LaptimerCore::LappyShellSettings LaptimerCore::TestHelper)

add_executable(test_ProcessManager test_ProcessManager.cpp)
target_link_libraries(test_ProcessManager PRIVATE Catch2::Catch2 Catch2::Catch2WithMain LaptimerCore::TestHelper LaptimerCore::LappyShellApplications Qt6::Test)
target_include_directories(test_ProcessManager PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_executable(dummy_process DummyProcess.cpp)

catch_discover_tests(test_ApplicationConfigReader)
catch_discover_tests(test_ApplicationVersion)
catch_discover_tests(test_ApplicationModel)
catch_discover_tests(test_ApplicationListModel)
catch_discover_tests(test_GlobalSettingsWriter)
