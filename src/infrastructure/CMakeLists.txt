add_library(infrastructure
    InMemTaskStorage.cpp
    InMemTagStorage.cpp
    TaskService.cpp
    TagService.cpp
)

target_include_directories(infrastructure PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(infrastructure PUBLIC core)