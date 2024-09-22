add_library(TestHelper OBJECT)
add_library(LaptimerCore::TestHelper ALIAS TestHelper)

target_sources(TestHelper
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tracks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Positions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MemorySessionDatabaseBackend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sessions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Laptimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SqliteDatabaseTestHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestSessionDownloaderClient.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Positions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Tracks.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MemorySessionDatabaseBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sessions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Laptimer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PositionDateTimeProvider.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SqliteDatabaseTestHelper.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestSessionDownloaderClient.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CompareHelper.hpp
)

target_include_directories(TestHelper
PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(TestHelper
PRIVATE
    LaptimerCore::CommonObject
    LaptimerCore::Positioning
    LaptimerCore::AlgorithmObject
    LaptimerCore::Storage
    LaptimerCore::Rest
    Catch2::Catch2
)

if(ENABLE_QT)
    target_sources(TestHelper
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/SettingsMemoryBackend.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/SettingsMemoryBackend.hpp

    )
    target_link_libraries(TestHelper
        PRIVATE
            LaptimerCore::CommonQt
    )
endif()
