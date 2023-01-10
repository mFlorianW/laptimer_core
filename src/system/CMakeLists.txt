add_library(System STATIC)
add_library(LaptimerCore::System ALIAS System)

target_sources(System
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Timer.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Timer.hpp
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
