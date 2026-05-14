add_subdirectory(core)
add_subdirectory(bussiness)
add_subdirectory(infrastructure)
# add_subdirectory(console)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    core
    bussiness
    infrastructure
    # console
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)