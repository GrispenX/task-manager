add_library(infrastructure
    InMemTaskStorage.cpp
    InMemTagStorage.cpp
    JSONTagSerializer.cpp
    JSONTaskSerializer.cpp
    JSONTagStorage.cpp
    JSONTaskStorage.cpp
    TaskService.cpp
    TagService.cpp
    TaskSelectorService.cpp
)

target_include_directories(infrastructure PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(infrastructure PUBLIC core)