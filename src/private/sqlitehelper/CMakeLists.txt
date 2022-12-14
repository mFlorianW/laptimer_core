add_library(SqliteHelper STATIC)
add_library(LaptimerCore::Private::SqliteHelper ALIAS SqliteHelper)

target_sources(SqliteHelper
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Statement.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Connection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Statement.hpp
)

target_link_libraries(SqliteHelper
PUBLIC
    SQLite::SQLite3
)

target_include_directories(SqliteHelper
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
