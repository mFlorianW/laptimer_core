add_library(Rest STATIC)
add_library(LaptimerCore::Rest ALIAS Rest)

target_sources(Rest
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RestGpsSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RestRequest.cpp
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IRestRequestHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/IRestServer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/RestGpsSource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/RestRequest.hpp
)

target_link_libraries(Rest
PUBLIC
    KDAB::KDBindings
    LaptimerCore::Positioning
)

target_include_directories(Rest
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

