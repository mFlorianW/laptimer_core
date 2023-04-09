# Ordering is important we don't want to enable AUTOMOC and AUTORCC for none qt parts.
add_subdirectory("ssd1322")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
add_subdirectory("qt")
