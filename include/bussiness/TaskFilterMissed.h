#ifndef INCLUDE_BUSSINESS_TASKFILTERMISSED_H_
#define INCLUDE_BUSSINESS_TASKFILTERMISSED_H_

#include "bussiness/ITaskFilterStrategy.h"

class TaskFilterMissed : public ITaskFilterStrategy
{
public:
    std::vector<std::shared_ptr<Task>> Filter(std::shared_ptr<ITaskStorage> task_storage) override;

    std::string Description() override;
};

#endif // INCLUDE_BUSSINESS_TASKFILTERMISSED_H_