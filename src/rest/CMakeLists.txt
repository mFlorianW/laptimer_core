add_library(Rest STATIC)
add_library(LaptimerCore::Rest ALIAS Rest)

target_sources(Rest
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/RestGpsSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestGpsSource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestRequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestRequest.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IRestRequestHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IRestServer.hpp
)

target_link_libraries(Rest
PUBLIC
    KDAB::KDBindings
    LaptimerCore::Positioning
)

target_include_directories(Rest
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

