#include "infrastructure/InMemTaskStorage.h"
#include <stdexcept>

int InMemTaskStorage::Add(std::shared_ptr<Task> task)
{
    int id = m_NextID++;
    task->SetID(id);
    m_Tasks.insert({id, task});
    return id;
}

std::shared_ptr<Task> InMemTaskStorage::Get(int id)
{
    auto it = m_Tasks.find(id);
    if(it == m_Tasks.end()) throw std::runtime_error("Task not found");
    return it->second;
}

std::vector<std::shared_ptr<Task>> InMemTaskStorage::Get(std::function<bool(std::shared_ptr<Task>)> predicate)
{
    std::vector<std::shared_ptr<Task>> suitable_tasks;
    for(auto [_, task] : m_Tasks)
    {
        if(predicate(task)) suitable_tasks.push_back(task);
    }
    return suitable_tasks;
}

std::vector<std::shared_ptr<Task>> InMemTaskStorage::GetAll()
{
    std::vector<std::shared_ptr<Task>> tasks;
    for(auto [_, task] : m_Tasks)
    {
        tasks.push_back(task);
    }
    return tasks;
}

void InMemTaskStorage::Remove(int id)
{
    m_Tasks.erase(id);
}