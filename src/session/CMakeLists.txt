add_library(Session STATIC)
add_library(LaptimerCore::Session ALIAS Session)

target_sources(Session
PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionDatabase.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/FileSystemSessionDatabaseBackend.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ISessionDatabase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ISessionDatabaseBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FileSystemSessionDatabaseBackend.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SessionDatabase.hpp
)

target_include_directories(Session
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Session
PUBLIC
    LaptimerCore::Common
)
