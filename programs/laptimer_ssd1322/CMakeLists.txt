add_definitions(-DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)

add_executable(laptimer_ssd1322)

target_sources(laptimer_ssd1322
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/laptimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Controls.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Controls.hpp
)

target_include_directories(laptimer_ssd1322
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(laptimer_ssd1322
PRIVATE
    lvgl-ssd1322-drivers::lvgl-ssd1322-drivers
    LaptimerCore::Ssd1322Shell
    LaptimerCore::LibraryPath
)
