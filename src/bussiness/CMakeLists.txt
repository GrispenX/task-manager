add_library(bussiness
    TaskFilterNoDeadline.cpp
    TaskFilterTimeLeft.cpp
    TaskFilterMissed.cpp
    TaskFilterByTag.cpp
)

target_include_directories(bussiness PUBLIC ${CMAKE_SOURCE_DIR}/include)