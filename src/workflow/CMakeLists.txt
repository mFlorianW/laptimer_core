add_library(Workflow OBJECT)
add_library(LaptimerCore::Workflow ALIAS Workflow)

target_sources(Workflow
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TrackDetectionWorkflow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ActiveSessionWorkflow.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ITrackDetectionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TrackDetectionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IActiveSessionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ActiveSessionWorkflow.hpp
)

target_include_directories(Workflow
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Workflow
PUBLIC
    LaptimerCore::Common
    LaptimerCore::Positioning
    LaptimerCore::Algorithm
    LaptimerCore::Session
)
