add_subdirectory(Common)
add_subdirectory(Shell)
add_subdirectory(Applications)

add_executable(lappy_shell)

target_sources(lappy_shell
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_shell.cpp
)

target_link_libraries(lappy_shell
PRIVATE
    Qt6::Widgets
    LaptimerCore::LappyShellApplications
    LaptimerCore::LappyShellApplicationsPlugin
    LaptimerCore::LappyShell
    LaptimerCore::LappyShellPlugin
)

install(TARGETS lappy_shell DESTINATION ${CMAKE_INSTALL_BINDIR})
