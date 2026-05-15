#ifndef INCLUDE_INFRASTRUCTURE_ITASKSELECTORSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_ITASKSELECTORSERVICE_H_

#include "bussiness/ITaskFilterStrategy.h"

class ITaskSelectorService
{
public:
    virtual ~ITaskSelectorService() = default;

    virtual void SetFilterStrategy(std::shared_ptr<ITaskFilterStrategy> filter) = 0;
    virtual std::shared_ptr<ITaskFilterStrategy> GetFilterStrategy() = 0;

    virtual std::vector<std::shared_ptr<Task>> GetTasks() = 0;
};

#endif // INCLUDE_INFRASTRUCTURE_ITASKSELECTORSERVICE_H_