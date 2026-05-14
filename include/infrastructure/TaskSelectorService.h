#ifndef INCLUDE_INFRASTRUCTURE_TASKSELECTORSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_TASKSELECTORSERVICE_H_

#include "infrastructure/ITaskSelectorService.h"

class TaskSelectorService : public ITaskSelectorService
{
public:
    TaskSelectorService(std::shared_ptr<ITaskStorage> task_storage);

    void SetFilterStrategy(std::shared_ptr<ITaskFilterStrategy> filter) override;

    std::vector<std::shared_ptr<Task>> GetTasks() override;

private:
    std::shared_ptr<ITaskStorage> m_TaskStorage;
    std::shared_ptr<ITaskFilterStrategy> m_TaskFilter;
};

#endif // INCLUDE_INFRASTRUCTURE_TASKSELECTORSERVICE_H_