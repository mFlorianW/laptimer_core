include(Catch)

# Create empty database on every build
add_custom_command(OUTPUT test_trackmanagement.db
    COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/test_trackmanagement.db && sqlite3 test_trackmanagement.db < "${CMAKE_SOURCE_DIR}/db/schema.sql"
    COMMAND sqlite3 "${CMAKE_CURRENT_BINARY_DIR}/test_trackmanagement.db" < "${CMAKE_CURRENT_SOURCE_DIR}/test_tracks.sql"
    DEPENDS ${CMAKE_SOURCE_DIR}/db/schema.sql
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_tracks.sql
VERBATIM)

add_custom_target(test_trackmangement_db ALL DEPENDS test_trackmanagement.db)

add_executable(test_SqliteTrackDatabase test_SqliteTrackDatabase.cpp)
target_link_libraries(test_SqliteTrackDatabase PRIVATE Catch2::Catch2 LaptimerCore::TrackManagement)
add_dependencies(test_SqliteTrackDatabase test_trackmangement_db)

catch_discover_tests(test_SqliteTrackDatabase)
