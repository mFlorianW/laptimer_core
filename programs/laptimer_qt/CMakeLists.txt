add_executable(laptimer_qt)

target_sources(laptimer_qt
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/laptimer_qt.cpp
)

target_include_directories(laptimer_qt
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(laptimer_qt
PRIVATE
    LaptimerCore::QtShell
    LaptimerCore::SystemQt
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
