add_library(System STATIC)
add_library(LaptimerCore::System ALIAS System)

target_sources(System
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private/SignalDispatcherRegistry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/private/SignalDispatcherRegistry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ISignalDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ISignalDispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SignalDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SignalDispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AsyncResult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AsyncResult.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FutureWatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DispatcherTypes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SystemTypes.hpp
)

target_link_libraries(System
PUBLIC
    KDAB::KDBindings
)

target_include_directories(System
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
