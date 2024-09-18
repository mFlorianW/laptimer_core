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
add_subdirectory(testhelper)
add_subdirectory(workflow)
add_subdirectory(positioning)
add_subdirectory(rest)
add_subdirectory(system)
add_subdirectory(storage)
add_subdirectory(lappy_shell)
