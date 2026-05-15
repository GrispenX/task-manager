#include "infrastructure/TaskSelectorService.h"
#include <stdexcept>

TaskSelectorService::TaskSelectorService(std::shared_ptr<ITaskStorage> task_storage) :
    m_TaskStorage(task_storage)
{

}

void TaskSelectorService::SetFilterStrategy(std::shared_ptr<ITaskFilterStrategy> filter)
{
    m_TaskFilter = filter;
}

std::shared_ptr<ITaskFilterStrategy> TaskSelectorService::GetFilterStrategy()
{
    return m_TaskFilter;
}

std::vector<std::shared_ptr<Task>> TaskSelectorService::GetTasks()
{
    if(!m_TaskFilter) return m_TaskStorage->GetAll();
    return m_TaskFilter->Filter(m_TaskStorage);
}