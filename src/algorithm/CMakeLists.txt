add_library(AlgorithmObject OBJECT)
add_library(LaptimerCore::AlgorithmObject ALIAS AlgorithmObject)

target_sources(AlgorithmObject
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrackDetection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DistanceCalculator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DistanceCalculator.hpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ITrackDetection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TrackDetection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ILaptimer.hpp
)

target_link_libraries(AlgorithmObject 
PUBLIC
    LaptimerCore::Common
)

target_include_directories(AlgorithmObject
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(Algorithm STATIC)
add_library(LaptimerCore::Algorithm ALIAS Algorithm)

target_link_libraries(Algorithm
PUBLIC
    LaptimerCore::AlgorithmObject
)