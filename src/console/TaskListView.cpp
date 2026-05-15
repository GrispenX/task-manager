#include "console/TaskListView.h"
#include "console/TasksView.h"
#include "console/TerminalStyle.h"
#include <iostream>
#include <format>

TaskListView::TaskListView(Context context) :
    m_Context(context)
{

}

std::unique_ptr<IView> TaskListView::Run()
{
    std::vector<std::shared_ptr<Task>> tasks = m_Context.task_selector_service->GetTasks();
    std::cout << "===== Task List =====\n\n";
    for(auto task : tasks)
    {
        std::optional<std::chrono::system_clock::time_point> deadline = task->Deadline();

        if(task->IsDone())
        {
            TerminalStyle::SetStrikethrough();
            TerminalStyle::SetForegroundColor(Color(175, 175, 175));
        }
        else if(deadline.has_value() && deadline.value() < std::chrono::system_clock::now())
        {
            TerminalStyle::SetUnderline();
            TerminalStyle::SetForegroundColor(Color(200, 0, 0));
        }
        
        std::cout << std::format("{}. {} ", task->ID(), task->Name());
        if(deadline.has_value())
        {
            std::cout << std::format("(due to {:%Y-%m-%d %H:%M:%S})", deadline.value());
        }
        TerminalStyle::ResetStyle();
        std::cout << "\n";
        
        for(auto tag : task->Tags())
        {
            TerminalStyle::SetBackgroundColor(tag->GetColor());
            std::cout << "  ";
            TerminalStyle::ResetStyle();
            std::cout << std::format(" {}. {} ", tag->GetID(), tag->GetLabel());
        }
        std::cout << "\n\n";
    }
    return std::make_unique<TasksView>(m_Context);
}