find_package(Qt5 REQUIRED COMPONENTS Core)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

add_library(lappy_shell_obj STATIC)
add_library(LaptimerCore::LappyShellObj ALIAS lappy_shell_obj)

target_sources(lappy_shell_obj
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationFinder.cpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationFinder.hpp
)

target_link_libraries(lappy_shell_obj
PUBLIC
    Qt5::Core
)

target_include_directories(lappy_shell_obj
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(lappy_shell)

qt5_add_resources(RESOURCE_FILES
)

target_sources(lappy_shell
PRIVATE
    ${RESOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_shell.cpp
)

target_link_libraries(lappy_shell
PRIVATE
    LaptimerCore::LappyShellObj
)
