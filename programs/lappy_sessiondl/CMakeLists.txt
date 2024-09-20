add_library(lappy_sessiondl_obj STATIC)
add_library(LaptimerCore::SessionDlObj ALIAS lappy_sessiondl_obj)

target_sources(lappy_sessiondl_obj
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/LappySessionDownloader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CliOptions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowModel.cpp

PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/CliOptions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindowModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LappySessionDownloader.hpp
)

target_link_libraries(lappy_sessiondl_obj
PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Network
    Qt6::Widgets
    LaptimerCore::RestQt
    LaptimerCore::SystemQt
    LaptimerCore::Workflow
    LaptimerCore::Storage
    LaptimerCore::LibraryPath
)

target_include_directories(lappy_sessiondl_obj
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_executable(lappy_sessiondl)

qt_add_resources(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc
)

target_sources(lappy_sessiondl
PRIVATE
    ${RESOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_sessiondl.cpp
)

target_link_libraries(lappy_sessiondl
PRIVATE
    LaptimerCore::SessionDlObj
)

set(TEST ${CMAKE_INSTALL_FULL_BINDIR})
set(APP_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/lappy_sessiondl.json)
configure_file(lappy_sessiondl.json.in ${APP_CONFIG})

install(TARGETS lappy_sessiondl DESTINATION ${BINDIR})
install(FILES ${APP_CONFIG} DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/lappy_sessiondl)
