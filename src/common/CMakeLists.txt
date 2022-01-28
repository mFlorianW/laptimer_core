# This code is need when the common library is not longer a
# header only lib.

# add_library(CommonObjekt OBJECT)
# add_library(LaptimerCore::CommonObjekt ALIAS CommonObjekt)

# target_sources(CommonObjekt
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/include/TrackData.hpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/include/PositionData.hpp
# )

# target_include_directories(CommonObjekt
#     PUBLIC
#         $<INSTALL_INTERFACE:include>
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     PRIVATE
#         ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

add_library(Common INTERFACE)
add_library(LaptimerCore::Common ALIAS Common)

# # Remove this, when the Common Library is not longer a header only
target_include_directories(Common INTERFACE
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# target_link_libraries(Common
#    LaptimerCore::CommonObjekt
# )