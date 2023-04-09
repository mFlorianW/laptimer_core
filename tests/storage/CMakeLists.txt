include(Catch)
# Create empty database on every build
add_custom_command(OUTPUT test_trackmanagement.db
    COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/test_trackmanagement.db && sqlite3 test_trackmanagement.db < "${CMAKE_SOURCE_DIR}/db/schema.sql"
    COMMAND sqlite3 "${CMAKE_CURRENT_BINARY_DIR}/test_trackmanagement.db" < "${CMAKE_CURRENT_SOURCE_DIR}/test_tracks.sql"
    DEPENDS ${CMAKE_SOURCE_DIR}/db/schema.sql
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_tracks.sql
VERBATIM)
add_custom_target(test_trackmangement_db ALL DEPENDS test_trackmanagement.db)

# Create empty database on every build
add_custom_command(OUTPUT test_session.db
    COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/test_session.db && sqlite3 test_session.db < "${CMAKE_SOURCE_DIR}/db/schema.sql"
    COMMAND sqlite3 "${CMAKE_CURRENT_BINARY_DIR}/test_session.db" < "${CMAKE_CURRENT_SOURCE_DIR}/test_session.sql"
    DEPENDS ${CMAKE_SOURCE_DIR}/db/schema.sql
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_session.sql
VERBATIM)
add_custom_target(test_session_db ALL DEPENDS test_session.db)

add_executable(test_SessionDatabase test_SessionDatabase.cpp)
target_link_libraries(test_SessionDatabase PRIVATE Catch2::Catch2 LaptimerCore::Storage LaptimerCore::TestHelper)

add_executable(test_FileSystemDataBaseBackend test_FileSystemSessionDatabaseBackend.cpp)
target_link_libraries(test_FileSystemDataBaseBackend PRIVATE Catch2::Catch2 LaptimerCore::Storage LaptimerCore::TestHelper)

add_executable(test_SqliteSessionDatabase test_SqliteSessionDatabase.cpp)
target_link_libraries(test_SqliteSessionDatabase PRIVATE Catch2::Catch2 LaptimerCore::Storage LaptimerCore::TestHelper)
add_dependencies(test_SqliteSessionDatabase test_session_db)

add_executable(test_SqliteTrackDatabase test_SqliteTrackDatabase.cpp)
target_link_libraries(test_SqliteTrackDatabase PRIVATE Catch2::Catch2 LaptimerCore::Storage LaptimerCore::TestHelper)
add_dependencies(test_SqliteTrackDatabase test_trackmangement_db)

catch_discover_tests(test_SessionDatabase)
catch_discover_tests(test_FileSystemDataBaseBackend)
catch_discover_tests(test_SqliteSessionDatabase)
catch_discover_tests(test_SqliteTrackDatabase)
