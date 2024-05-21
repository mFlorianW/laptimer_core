add_library(System STATIC)
add_library(LaptimerCore::System ALIAS System)

target_sources(System
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/PosixTimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/PosixTimer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AsyncResult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AsyncResult.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FutureWatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EventLoop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EventLoop.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.hpp
)

target_link_libraries(System
PUBLIC
    KDAB::KDBindings
)

target_include_directories(System
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
