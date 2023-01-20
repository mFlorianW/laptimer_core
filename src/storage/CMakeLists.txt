add_library(Storage STATIC)
add_library(LaptimerCore::Storage ALIAS Storage)

target_sources(Storage
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/private/Connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/private/Connection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/private/Statement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/private/Statement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FileSystemSessionDatabaseBackend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FileSystemSessionDatabaseBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ISessionDatabase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ISessionDatabaseBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ITrackDatabase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionDatabase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionDatabase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SqliteSessionDatabase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SqliteSessionDatabase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SqliteTrackDatabase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SqliteTrackDatabase.hpp
)

target_link_libraries(Storage
PUBLIC
    SQLite::SQLite3 
    KDAB::KDBindings
    LaptimerCore::System
    LaptimerCore::Common
)

target_include_directories(Storage
PUBLIC
    $<INSTALL_INTERFACE:src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
