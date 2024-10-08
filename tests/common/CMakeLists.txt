include(Catch)

add_executable(test_SharedDataPointer test_SharedDataPointer.cpp)
target_link_libraries(test_SharedDataPointer PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_LapData test_LapData.cpp)
target_link_libraries(test_LapData PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_Timestamp test_Timestamp.cpp)
target_link_libraries(test_Timestamp PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_Date test_Date.cpp)
target_link_libraries(test_Date PRIVATE Catch2::Catch2 LaptimerCore::Common)

add_executable(test_JsonSerializer test_JsonSerializer.cpp)
target_link_libraries(test_JsonSerializer PRIVATE Catch2::Catch2 LaptimerCore::Common LaptimerCore::TestHelper)

add_executable(test_JsonDeserializer test_JsonDeserializer.cpp)
target_link_libraries(test_JsonDeserializer PRIVATE Catch2::Catch2 LaptimerCore::Common LaptimerCore::TestHelper)

add_executable(test_PositionDateTime test_PositionDateTime.cpp)
target_link_libraries(test_PositionDateTime PRIVATE Catch2::Catch2 LaptimerCore::Common LaptimerCore::TestHelper)

catch_discover_tests(test_SharedDataPointer)
catch_discover_tests(test_LapData)
catch_discover_tests(test_Timestamp)
catch_discover_tests(test_Date)
catch_discover_tests(test_JsonSerializer)
catch_discover_tests(test_JsonDeserializer)
catch_discover_tests(test_PositionDateTime)

if(ENABLE_QT)
    add_executable(test_GlobalSettingsReader test_GlobalSettingsReader.cpp)
    target_link_libraries(test_GlobalSettingsReader PRIVATE Catch2::Catch2 Catch2::Catch2WithMain LaptimerCore::CommonQt LaptimerCore::TestHelper)
endif()
