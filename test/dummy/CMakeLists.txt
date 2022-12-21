add_library(TestDummy OBJECT)
add_library(LaptimerCore::TestDummy ALIAS TestDummy)

target_sources(TestDummy
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tracks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Positions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MemorySessionDatabaseBackend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sessions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Laptimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SqliteDatabaseTestHelper.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Positions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Tracks.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MemorySessionDatabaseBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sessions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Laptimer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PositionDateTimeProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SqliteDatabaseTestHelper.hpp
)

target_include_directories(TestDummy
PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(TestDummy
PRIVATE
    LaptimerCore::CommonObject
    LaptimerCore::Positioning
    LaptimerCore::AlgorithmObject
    LaptimerCore::Session
    Catch2::Catch2
)
