add_library(Session STATIC)
add_library(LaptimerCore::Session ALIAS Session)

target_sources(Session
PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionDatabase.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ISessionDatabase.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/Session.hpp
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
