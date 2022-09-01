add_definitions(-DLV_CONF_INCLUDE_SIMPLE=1 -DLV_LVGL_H_INCLUDE_SIMPLE)

add_executable(laptimer)

target_sources(laptimer
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/laptimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Controls.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Controls.hpp
)

target_include_directories(laptimer
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(laptimer
PRIVATE
    LaptimerCore::Ssd1322Shell
)
