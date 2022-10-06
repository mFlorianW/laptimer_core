include(CTest)
if(ENABLE_CATCH2_FETCH)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.7
    )
    FetchContent_MakeAvailable(Catch2)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
else(ENABLE_CATCH2_FETCH)
    find_package(Catch2 CONFIG REQUIRED)
endif(ENABLE_CATCH2_FETCH)

add_subdirectory(algorithm)
add_subdirectory(common)
add_subdirectory(dummy)
add_subdirectory(workflow)
add_subdirectory(session)
add_subdirectory(positioning)
