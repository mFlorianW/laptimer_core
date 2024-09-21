add_subdirectory(SessionDl)
add_executable(lappy_sessiondl)

target_sources(lappy_sessiondl
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lappy_sessiondl.cpp
)

target_link_libraries(lappy_sessiondl
PRIVATE
    LaptimerCore::LappySessionDl
    LaptimerCore::LappySessionDlPlugin
)

set(LAPPY_SESSION_DL_DATADIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/lappy_sessiondl)
set(TEST ${CMAKE_INSTALL_FULL_BINDIR})
set(ICON_URL ${LAPPY_SESSION_DL_DATADIR})
set(APP_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/lappy_sessiondl.json)
configure_file(lappy_sessiondl.json.in ${APP_CONFIG})

install(TARGETS lappy_sessiondl DESTINATION ${BINDIR})
install(FILES ${APP_CONFIG} DESTINATION ${LAPPY_SESSION_DL_DATADIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lappy_sessiondl.svg DESTINATION ${LAPPY_SESSION_DL_DATADIR})
