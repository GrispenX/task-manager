#ifndef INCLUDE_BUSSINESS_TASKFILTERNODEADLINE_H_
#define INCLUDE_BUSSINESS_TASKFILTERNODEADLINE_H_

#include "bussiness/ITaskFilterStrategy.h"

class TaskFilterNoDeadline : public ITaskFilterStrategy
{
public:
    std::vector<std::shared_ptr<Task>> Filter(std::shared_ptr<ITaskStorage> task_storage) override;

    std::string Description() override;
};

#endif // INCLUDE_BUSSINESS_TASKFILTERNODEADLINE_H_