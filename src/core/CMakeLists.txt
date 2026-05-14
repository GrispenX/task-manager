add_library(core
    Color.cpp
    Tag.cpp
    Task.cpp
)

target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)