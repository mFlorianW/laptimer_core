find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Widgets)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

add_library(lappy_shell_obj STATIC)
add_library(LaptimerCore::LappyShellObj ALIAS lappy_shell_obj)

target_sources(lappy_shell_obj
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationFinder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfigReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationListModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappyShell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LoggingCategories.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LoggingCategories.hpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationFinder.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfigReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationListModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappyShell.hpp
)

target_link_libraries(lappy_shell_obj
PRIVATE
    LaptimerCore::DatabaseFile
PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Widgets
)

target_include_directories(lappy_shell_obj
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(lappy_shell)

qt_add_resources(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc
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

install(TARGETS lappy_shell DESTINATION ${BINDIR})
