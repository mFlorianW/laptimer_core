add_library(TrackManagement OBJECT)
add_library(LaptimerCore::TrackManagement ALIAS TrackManagement)

target_sources(TrackManagement
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SqliteTrackDatabase.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ITrackDatabase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SqliteTrackDatabase.hpp
)

target_include_directories(TrackManagement
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(TrackManagement
PUBLIC
    LaptimerCore::Private::SqliteHelper
    LaptimerCore::Common
)
