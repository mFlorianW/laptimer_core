add_library(Rest STATIC)
add_library(LaptimerCore::Rest ALIAS Rest)

target_sources(Rest
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GpsEndpoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GpsEndpoint.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestRequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestRequest.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IRestRequestHandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IRestServer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SessionEndpoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SessionEndpoint.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Path.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Path.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestCall.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RestCall.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IRestClient.hpp
)

target_link_libraries(Rest
PUBLIC
    KDAB::KDBindings
    LaptimerCore::Positioning
    LaptimerCore::Storage
)

target_include_directories(Rest
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if(ENABLE_QT)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    add_subdirectory(qt)
endif()


