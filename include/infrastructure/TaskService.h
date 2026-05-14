#ifndef INCLUDE_INFRASTRUCTURE_TASKSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_TASKSERVICE_H_

#include "infrastructure/ITaskService.h"
#include "core/ITaskStorage.h"

class TaskService : public ITaskService
{
public:
    TaskService(std::shared_ptr<ITaskStorage> task_storage);
    
    int CreateNewTask(std::string name, std::optional<int> parent_id) override;
    void SwitchTaskStatus(int task_id) override;
    void DeleteTask(int task_id) override;
    void SetTaskName(int task_id, std::string name) override;
    void SetTaskDescription(int task_id, std::string description) override;
    void SetTaskDeadline(int task_id, std::chrono::system_clock::time_point deadline) override;
    void RemoveTaskDeadline(int task_id) override;
    std::optional<std::shared_ptr<Task>> GetTask(int task_id) override;

private:
    std::shared_ptr<ITaskStorage> m_TaskStorage;
};

#endif // INCLUDE_INFRASTRUCTURE_TASKSERVICE_H_