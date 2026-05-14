add_library(infrastructure
    InMemTaskStorage.cpp
)

target_include_directories(infrastructure PUBLIC ${CMAKE_SOURCE_DIR}/include)