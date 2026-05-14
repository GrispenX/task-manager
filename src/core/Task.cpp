#include "core/Task.h"
#include <stdexcept>
#include <algorithm>

Task::Task(TaskOptions options) :
    m_ID(options.id),
    m_Name(options.name),
    m_Description(options.description),
    m_IsDone(options.is_done),
    m_Deadline(options.deadline)
{
    if(options.name.empty()) throw std::runtime_error("Name can't be empty");
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

std::vector<std::shared_ptr<Tag>> Task::Tags()
{
    return m_Tags;
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

void Task::RemoveSubtask(std::shared_ptr<Task> task)
{
    std::erase(m_Subtasks, task);
}

void Task::AddTag(std::shared_ptr<Tag> tag)
{
    m_Tags.push_back(tag);
}

void Task::RemoveTag(std::shared_ptr<Tag> tag)
{
    std::erase(m_Tags, tag);
}

bool Task::HasTag(std::shared_ptr<Tag> tag)
{
    for(auto t : m_Tags)
    {
        if(t == tag) return true;
    }
    return false;
}