find_package(Qt5 REQUIRED COMPONENTS Core EventDispatcherSupport)

add_library(SystemQt SHARED)
add_library(LaptimerCore::SystemQt ALIAS SystemQt)

target_sources(SystemQt
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/QEventDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QEventDispatcher.hpp
)

target_link_libraries(SystemQt
PUBLIC
    LaptimerCore::System
    Qt5::Core
    Qt5::CorePrivate
    Qt5::EventDispatcherSupport
    Qt5::EventDispatcherSupportPrivate
)

target_include_directories(SystemQt
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_definitions(SystemQt PRIVATE QT_NO_KEYWORDS)
