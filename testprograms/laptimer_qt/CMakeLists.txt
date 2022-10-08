find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

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
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
