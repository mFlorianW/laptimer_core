add_library(CommonObject OBJECT)
add_library(LaptimerCore::CommonObject ALIAS CommonObject)

target_sources(CommonObject
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrackData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PositionData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Timestamp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LapData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SessionData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Date.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/JsonSerializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/JsonDeserializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PositionDateTimeData.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TrackData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/PositionData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SharedDataPointer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Timestamp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/LapData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SessionData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Date.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonSerializer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/JsonDeserializer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/PositionDateTimeData.hpp
)

target_include_directories(CommonObject
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(CommonObject
PUBLIC
    KDAB::KDBindings
)

add_library(Common STATIC)
add_library(LaptimerCore::Common ALIAS Common)

target_link_libraries(Common
PUBLIC
    LaptimerCore::CommonObject
)
