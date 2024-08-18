macro(fetch_arduinojson)
    FetchContent_Declare(
        ArduinoJson
        GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
        GIT_TAG        v6.19.3
    )
    FetchContent_MakeAvailable(ArduinoJson)
    include_directories(SYSTEM ${arduinojson_SOURCE_DIR}/src)
endmacro()
