add_executable(lappy_headless)

target_sources(lappy_headless
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_headless.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappyHeadless.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappyHeadless.hpp
)

target_include_directories(lappy_headless
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(lappy_headless
PRIVATE
    LaptimerCore::LibraryPath
    LaptimerCore::System
    LaptimerCore::Positioning
    LaptimerCore::Storage
)
