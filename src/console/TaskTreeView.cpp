#include "console/TaskTreeView.h"
#include "console/TasksView.h"
#include "console/TerminalStyle.h"
#include <iostream>
#include <format>

TaskTreeView::TaskTreeView(Context context) :
    m_Context(context)
{

}

std::unique_ptr<IView> TaskTreeView::Run()
{
    std::cout << "===== Task Tree =====\n\n";
    
    for(auto orphan : m_Context.task_service->GetOrphanTasks())
    {
        PrintTaskRecursively(orphan);
        std::cout << "\n";
    }

    return std::make_unique<TasksView>(m_Context);
}

void TaskTreeView::PrintTaskRecursively(std::shared_ptr<Task> task, std::string prefix)
{
    std::optional<std::chrono::system_clock::time_point> deadline = task->Deadline();
    std::cout << prefix;

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
    
    std::cout << prefix;
    for(auto tag : task->Tags())
    {
        std::cout << "[";
        TerminalStyle::SetBackgroundColor(tag->GetColor());
        std::cout << "  ";
        TerminalStyle::ResetStyle();
        std::cout << std::format(" {}. {}] ", tag->GetID(), tag->GetLabel());
    }
    std::cout << "\n\n";

    for(auto subtask : task->Subtasks())
    {
        PrintTaskRecursively(subtask, prefix + "    ");
    }
}