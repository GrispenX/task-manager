#include "infrastructure/InMemTaskStorage.h"
#include "infrastructure/InMemTagStorage.h"
#include "infrastructure/TaskService.h"
#include "infrastructure/TagService.h"
#include "infrastructure/TaskSelectorService.h"
#include <iostream>
#include <format>
#include "console/MainView.h"

using namespace std::chrono;

class BGColor : public Color {};

std::ostream& operator<<(std::ostream& os, const BGColor& color)
{
    std::cout << std::format("\033[48;2;{};{};{}m", color.R(), color.G(), color.B());
    return os;
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
    std::cout << std::format("\033[38;2;{};{};{}m", color.R(), color.G(), color.B());
    return os;
}

void PrintTask(std::shared_ptr<Task> task, std::string prefix = "")
{
    std::cout << prefix << "ID: " << task->ID() << "\n";
    std::cout << prefix << "Label: " << task->Name() << "\n";
    for(auto tag : task->Tags())
    {
        std::cout << prefix << "  " << BGColor(tag->GetColor()) << "  \033[0m " << tag->GetID() << ". " << tag->GetLabel() << "\n";
    }
    std::cout << "\n";
}

void PrintTaskTree(std::shared_ptr<Task> task, std::string prefix = "")
{
    PrintTask(task, prefix);
    for(auto subtask : task->Subtasks())
    {
        PrintTaskTree(subtask, prefix + "    ");
    }
}

int main()
{
    std::shared_ptr<ITaskStorage> task_storage = std::make_shared<InMemTaskStorage>();
    std::shared_ptr<ITagStorage> tag_storage = std::make_shared<InMemTagStorage>();
    Context context {
        .task_service = std::make_shared<TaskService>(task_storage),
        .tag_service = std::make_shared<TagService>(tag_storage, task_storage),
        .task_selector_service = std::make_shared<TaskSelectorService>(task_storage)
    };

    std::unique_ptr<IView> view = std::make_unique<MainView>(context);
    while(view)
    {
        view = std::move(view->Run());
    }
}