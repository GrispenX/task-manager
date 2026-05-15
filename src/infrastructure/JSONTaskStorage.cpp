#include "infrastructure/JSONTaskStorage.h"
#include <stdexcept>
#include <fstream>

void JSONTaskStorage::AddRecursively(std::shared_ptr<Task> task)
{
    int id = task->ID();
    if(id >= m_NextID) m_NextID = id + 1;
    m_Tasks.insert({id, task});
    for(auto subtask : task->Subtasks())
    {
        AddRecursively(subtask);
    }
}

JSONTaskStorage::JSONTaskStorage(JSONTaskSerializer serializer, std::filesystem::path file_path) :
    m_TaskSerializer(serializer),
    m_FilePath(file_path)
{
    if(!std::filesystem::exists(m_FilePath)) return;

    std::ifstream file(m_FilePath);
    nlohmann::json j = nlohmann::json::parse(file);
    file.close();

    for(auto task_json : j)
    {
        std::shared_ptr<Task> task = m_TaskSerializer.Deserialize(task_json);
        AddRecursively(task);
    }
}

JSONTaskStorage::~JSONTaskStorage()
{
    nlohmann::json j = nlohmann::json::array();
    for(auto orphan : Get([](std::shared_ptr<Task> task) { return task->ParentTask().lock() == nullptr; }))
    {
        j.push_back(m_TaskSerializer.Serialize(orphan));
    }

    std::ofstream file(m_FilePath);
    file << j.dump(4);
    file.close();
}

int JSONTaskStorage::Add(std::shared_ptr<Task> task)
{
    int id = m_NextID++;
    task->SetID(id);
    m_Tasks.insert({id, task});
    return id;
}

std::shared_ptr<Task> JSONTaskStorage::Get(int id)
{
    auto it = m_Tasks.find(id);
    if(it == m_Tasks.end()) throw std::runtime_error("Task not found");
    return it->second;
}

std::vector<std::shared_ptr<Task>> JSONTaskStorage::Get(std::function<bool(std::shared_ptr<Task>)> predicate)
{
    std::vector<std::shared_ptr<Task>> suitable_tasks;
    for(auto [_, task] : m_Tasks)
    {
        if(predicate(task)) suitable_tasks.push_back(task);
    }
    return suitable_tasks;
}

std::vector<std::shared_ptr<Task>> JSONTaskStorage::GetAll()
{
    std::vector<std::shared_ptr<Task>> tasks;
    for(auto [_, task] : m_Tasks)
    {
        tasks.push_back(task);
    }
    return tasks;
}

void JSONTaskStorage::Remove(int id)
{
    m_Tasks.erase(id);
}