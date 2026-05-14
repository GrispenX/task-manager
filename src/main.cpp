#include "infrastructure/InMemTaskStorage.h"
#include <iostream>
#include <format>

int main()
{
    std::shared_ptr<Task> task1 = std::make_shared<Task>(0, "task 1", "description", false);
    std::shared_ptr<Task> task2 = std::make_shared<Task>(0, "task 2", "description", false);
    std::shared_ptr<Task> task3 = std::make_shared<Task>(0, "task 3", "description", false);
    std::shared_ptr<Task> task4 = std::make_shared<Task>(0, "task 4", "description", false);
    std::shared_ptr<Task> task5 = std::make_shared<Task>(0, "task 5", "description", false);

    task1->AddSubtask(task2);
    task1->AddSubtask(task3);

    task2->AddSubtask(task4);
    task4->AddSubtask(task5);

    InMemTaskStorage storage;
    storage.Add(task1);
    storage.Add(task2);
    storage.Add(task3);
    storage.Add(task4);
    storage.Add(task5);


    for(const auto& task : storage.GetAll())
    {
        std::cout << std::format("ID: {}\nName: {}\n", task->ID(), task->Name());
        auto parent = task->ParentTask().lock();
        if(parent) std::cout << "Parent: " << parent->ID() << "\n";
        std::cout << "\n";
    }
}