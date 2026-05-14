#include "infrastructure/TaskService.h"
#include <queue>

TaskService::TaskService(std::shared_ptr<ITaskStorage> task_storage) :
    m_TaskStorage(task_storage)
{

}

int TaskService::CreateNewTask(std::string name, std::optional<int> parent_id)
{
    TaskOptions options {
        .name = name
    };
    std::shared_ptr<Task> task = std::make_shared<Task>(options);

    if(parent_id.has_value())
    {
        m_TaskStorage->Get(parent_id.value())->AddSubtask(task);
    }

    return m_TaskStorage->Add(task);
}

void TaskService::SwitchTaskStatus(int task_id)
{
    std::shared_ptr<Task> task = m_TaskStorage->Get(task_id);
    task->SetDone(!task->IsDone());
}

void TaskService::DeleteTask(int task_id)
{
    std::shared_ptr<Task> task = m_TaskStorage->Get(task_id);
    std::queue<std::shared_ptr<Task>> to_delete;
    to_delete.push(task);

    while(to_delete.empty())
    {
        for(auto subtask : to_delete.front()->Subtasks())
        {
            to_delete.push(subtask);
        }
        m_TaskStorage->Remove(to_delete.front()->ID());
        to_delete.pop();
    }

    auto parent = task->ParentTask().lock();
    if(parent)
    {
        parent->RemoveSubtask(task);
    }
}

void TaskService::SetTaskName(int task_id, std::string name)
{
    m_TaskStorage->Get(task_id)->SetName(name);
}

void TaskService::SetTaskDescription(int task_id, std::string description)
{
    m_TaskStorage->Get(task_id)->SetDescription(description);
}

void TaskService::SetTaskDeadline(int task_id, std::chrono::system_clock::time_point deadline)
{
    m_TaskStorage->Get(task_id)->SetDeadline(deadline);
}

void TaskService::RemoveTaskDeadline(int task_id)
{
    m_TaskStorage->Get(task_id)->SetDeadline(std::nullopt);
}

std::optional<std::shared_ptr<Task>> TaskService::GetTask(int task_id)
{
    try
    {
        return m_TaskStorage->Get(task_id);
    }
    catch(const std::exception& e)
    {
        return std::nullopt;
    }
}