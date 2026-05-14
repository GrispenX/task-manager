add_library(console
    TerminalStyle.cpp
    MainView.cpp
    TagsView.cpp
    TasksView.cpp
    TaskDetailedView.cpp
)

target_include_directories(console PUBLIC ${CMAKE_SOURCE_DIR}/include)