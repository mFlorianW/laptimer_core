add_library(TestDummy OBJECT)
add_library(LaptimerCore::TestDummy ALIAS TestDummy)

target_sources(TestDummy
PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/PositionInformationProvider.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Tracks.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Positions.cpp
PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/PositionInformationProvider.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Positions.hpp
)

target_include_directories(TestDummy
PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(TestDummy
PUBLIC
    LaptimerCore::CommonObject
    LaptimerCore::Positioning
    LaptimerCore::AlgorithmObject
)