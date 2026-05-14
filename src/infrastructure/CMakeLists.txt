add_library(infrastructure
    InMemTaskStorage.cpp
    TaskService.cpp
)

target_include_directories(infrastructure PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(infrastructure PUBLIC core)