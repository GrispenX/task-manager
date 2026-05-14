#include "core/Task.h"
#include <stdexcept>

Task::Task(
    std::string name,
    std::string description,
    bool is_done,
    int id,
    std::optional<std::chrono::time_point<std::chrono::system_clock>> deadline
) :
    m_ID(id),
    m_Name(name),
    m_Description(description),
    m_IsDone(is_done),
    m_Deadline(deadline)
{

}

int Task::ID() const
{
    return m_ID;
}

std::string Task::Name() const
{
    return m_Name;
}

std::string Task::Description() const
{
    return m_Description;
}

bool Task::IsDone() const
{
    return m_IsDone;
}

std::optional<std::chrono::time_point<std::chrono::system_clock>> Task::Deadline() const
{
    return m_Deadline;
}

std::vector<std::shared_ptr<Task>> Task::Subtasks() const
{
    return m_Subtasks;
}

std::weak_ptr<Task> Task::ParentTask() const
{
    return m_ParentTask;
}


void Task::SetID(int id)
{
    m_ID = id;
}

void Task::SetName(std::string name)
{
    if(name.empty()) throw std::runtime_error("Name can't be empty");
    m_Name = name;
}

void Task::SetDescription(std::string description)
{
    m_Description = description;
}

void Task::SetDone(bool is_done)
{
    m_IsDone = is_done;
}

void Task::SetDeadline(std::optional<std::chrono::time_point<std::chrono::system_clock>> deadline)
{
    m_Deadline = deadline;
}

void Task::AddSubtask(std::shared_ptr<Task> task)
{
    if(task == nullptr) throw std::runtime_error("Subtask can't be nullptr");
    if(task->m_ParentTask.lock() != nullptr) throw std::runtime_error("Task already have a parent");
    if(m_ParentTask.lock() == task) throw std::runtime_error("Task can't be a parent of itself");

    m_Subtasks.push_back(task);
    task->m_ParentTask = shared_from_this();
}