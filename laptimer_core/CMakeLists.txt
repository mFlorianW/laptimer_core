idf_component_register(
SRC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/common/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/algorithm/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/workflow/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/view
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/viewmodel
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/session/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/positioning/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/track_management/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/private/sqlitehelper/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/rest/src
PRIV_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/command
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/view
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/src/viewmodel
INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/algorithm/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/common/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/positioning/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/workflow/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/shell/ssd1322/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/session/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/track_management/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/private/sqlitehelper/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/rest/include"
EXCLUDE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/session/src/FileSystemSessionDatabaseBackend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/session/inc/FileSystemSessionDatabaseBackend.hpp
)

add_custom_command(OUTPUT laptimer_core.db
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/db
    COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/db/laptimer_core.db && sqlite3 ${CMAKE_CURRENT_BINARY_DIR}/db/laptimer_core.db < "${CMAKE_CURRENT_SOURCE_DIR}/../db/schema.sql"
    COMMAND sqlite3 "${CMAKE_CURRENT_BINARY_DIR}/db/laptimer_core.db" < "${CMAKE_CURRENT_SOURCE_DIR}/../db/track.sql"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../db/schema.sql
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../db/track.sql
    VERBATIM)
add_custom_target(db DEPENDS laptimer_core.db)
add_dependencies(${COMPONENT_TARGET} db)
spiffs_create_partition_image(session ${CMAKE_CURRENT_BINARY_DIR}/db DEPENDS db FLASH_IN_PROJECT)