#ifndef INCLUDE_INFRASTRUCTURE_ITASKSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_ITASKSERVICE_H_

#include "core/Task.h"

class ITaskService
{
public:
    virtual ~ITaskService() = default;

    virtual int CreateNewTask(std::string name, std::optional<int> parent_id) = 0;
    virtual void SwitchTaskStatus(int task_id) = 0;
    virtual void DeleteTask(int task_id) = 0;
    virtual void SetTaskName(int task_id, std::string name) = 0;
    virtual void SetTaskDescription(int task_id, std::string description) = 0;
    virtual void SetTaskDeadline(int task_id, std::chrono::system_clock::time_point deadline) = 0;
    virtual void RemoveTaskDeadline(int task_id) = 0;
    virtual std::optional<std::shared_ptr<Task>> GetTask(int task_id) = 0;
    virtual std::vector<std::shared_ptr<Task>> GetOrphanTasks() = 0;
};

#endif // INCLUDE_INFRASTRUCTURE_ITASKSERVICE_H_