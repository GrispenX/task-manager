#ifndef INCLUDE_INFRASTRUCTURE_TASKSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_TASKSERVICE_H_

#include "infrastructure/ITaskService.h"
#include "core/ITaskStorage.h"

class TaskService : public ITaskService
{
public:
    TaskService(std::shared_ptr<ITaskStorage> task_storage);
    
    int CreateNewTask(std::string name, std::string description, std::optional<int> parent_id) override;
    void SwitchTaskStatus(int task_id) override;
    void DeleteTask(int task_id) override;

private:
    std::shared_ptr<ITaskStorage> m_TaskStorage;
};

#endif // INCLUDE_INFRASTRUCTURE_TASKSERVICE_H_