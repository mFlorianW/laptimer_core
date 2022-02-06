add_library(CommonObject OBJECT)
add_library(LaptimerCore::CommonObject ALIAS CommonObject)

target_sources(CommonObject
PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/src/TrackData.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/PositionData.cpp
PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include/TrackData.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/PositionData.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/SharedDataPointer.hpp
)

target_include_directories(CommonObject
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(Common STATIC)
add_library(LaptimerCore::Common ALIAS Common)

target_link_libraries(Common
PUBLIC
    LaptimerCore::CommonObject
)