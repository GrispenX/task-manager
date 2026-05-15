find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}Test
    TagServiceTest.cpp
    TaskServiceTest.cpp
)

target_link_libraries(${PROJECT_NAME}Test PRIVATE
    core
    bussiness
    infrastructure
)

target_include_directories(${PROJECT_NAME}Test PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}Test PRIVATE GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}Test)