# Create empty database on every build
add_custom_command(OUTPUT laptimer_core.db
    COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/laptimer_core.db && sqlite3 laptimer_core.db < "${CMAKE_CURRENT_SOURCE_DIR}/schema.sql"
    COMMAND sqlite3 "${CMAKE_CURRENT_BINARY_DIR}/laptimer_core.db" < "${CMAKE_CURRENT_SOURCE_DIR}/track.sql"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/schema.sql
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/track.sql
    VERBATIM)

add_custom_target(db ALL DEPENDS laptimer_core.db)

set(LIBRARY_FILE ${CMAKE_CURRENT_BINARY_DIR}/laptimer_core.db)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LibraryPath.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/LibraryPath.hpp @ONLY)

add_library(LibraryPath INTERFACE)
add_library(LaptimerCore::LibraryPath ALIAS LibraryPath)
add_dependencies(LibraryPath db)

target_include_directories(LibraryPath
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
