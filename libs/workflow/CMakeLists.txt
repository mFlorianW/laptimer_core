add_library(Workflow OBJECT)
add_library(LaptimerCore::Workflow ALIAS Workflow)

target_sources(Workflow
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ITrackDetectionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackDetectionWorkflow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackDetectionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IActiveSessionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActiveSessionWorkflow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActiveSessionWorkflow.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ISessionDownload.hpp
)

target_include_directories(Workflow
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Workflow
PUBLIC
    LaptimerCore::Common
    LaptimerCore::Positioning
    LaptimerCore::Algorithm
    LaptimerCore::Storage
)
