#include "infrastructure/InMemTaskStorage.h"
#include "infrastructure/InMemTagStorage.h"
#include "infrastructure/TaskService.h"
#include "infrastructure/TagService.h"
#include <iostream>
#include <format>

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

void PrintTaskTree(std::shared_ptr<Task> task, std::string prefix = "")
{
    std::cout << prefix << "ID: " << task->ID() << "\n";
    std::cout << prefix << "Label: " << task->Name() << "\n";
    for(auto tag : task->Tags())
    {
        std::cout << prefix << "  " << BGColor(tag->GetColor()) << "  \033[0m " << tag->GetID() << ". " << tag->GetLabel() << "\n";
    }
    for(auto subtask : task->Subtasks())
    {
        PrintTaskTree(subtask, prefix + "    ");
    }
}

int main()
{
    std::shared_ptr<ITaskStorage> task_storage = std::make_shared<InMemTaskStorage>();
    std::shared_ptr<ITagStorage> tag_storage = std::make_shared<InMemTagStorage>();
    TaskService task_service(task_storage);
    TagService tag_service(tag_storage, task_storage);
    int id1 = task_service.CreateNewTask("task 1", "", std::nullopt);
    int id2 = task_service.CreateNewTask("task 2", "", id1);
    int id3 = task_service.CreateNewTask("task 3", "", id1);
    int id4 = task_service.CreateNewTask("task 4", "", id2);
    int id5 = task_service.CreateNewTask("task 5", "", id4);

    int tag1 = tag_service.CreateTag("Blue", Blue);
    int tag2 = tag_service.CreateTag("Yellow", Yellow);
    int tag3 = tag_service.CreateTag("Red", Red);

    tag_service.AddTagToTask(id1, tag1);
    tag_service.AddTagToTask(id1, tag2);
    tag_service.AddTagToTask(id5, tag3);
    tag_service.AddTagToTask(id5, tag1);

    std::shared_ptr<Task> root = task_storage->Get(id1);
    PrintTaskTree(root);
}