add_library(System STATIC)
add_library(LaptimerCore::System ALIAS System)

target_sources(System
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FutureWatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ISignalDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SignalDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SignalDispatcherRegistry.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Timer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/FutureWatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ISignalDispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SignalDispatcher.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SystemTypes.hpp
)

target_link_libraries(System
PUBLIC
    KDAB::KDBindings
)

target_include_directories(System
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
