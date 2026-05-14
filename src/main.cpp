#include "infrastructure/InMemTaskStorage.h"
#include "infrastructure/TaskService.h"
#include <iostream>
#include <format>

void PrintTaskTree(std::shared_ptr<Task> task, int depth = 0)
{
    std::string prefix;
    for(int i = 0; i < depth; i++) prefix.append("\t");
    std::cout << std::format("{}ID: {}\n{}Name: {}\n\n", prefix, task->ID(), prefix, task->Name());
    for(auto subtask : task->Subtasks())
    {
        PrintTaskTree(subtask, depth + 1);
    }
}

int main()
{
    std::shared_ptr<ITaskStorage> storage = std::make_shared<InMemTaskStorage>();
    TaskService service(storage);
    int id1 = service.CreateNewTask("task 1", "", std::nullopt);
    int id2 = service.CreateNewTask("task 2", "", id1);
    int id3 = service.CreateNewTask("task 3", "", id1);
    int id4 = service.CreateNewTask("task 4", "", id2);
    int id5 = service.CreateNewTask("task 5", "", id4);

    service.DeleteTask(id2);

    std::shared_ptr<Task> root = storage->Get(id1);
    PrintTaskTree(root);
}