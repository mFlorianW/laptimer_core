add_executable(rapid_headless)

target_sources(rapid_headless
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_headless.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappyHeadless.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappyHeadless.hpp
)

target_include_directories(rapid_headless
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(rapid_headless
PRIVATE
    Rapid::LibraryPath
    LaptimerCore::System
    LaptimerCore::Positioning
    LaptimerCore::Storage
    LaptimerCore::Workflow
)
