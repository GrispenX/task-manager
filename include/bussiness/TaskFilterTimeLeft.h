#ifndef INCLUDE_BUSSINESS_TASKFILTERTIMELEFT_H_
#define INCLUDE_BUSSINESS_TASKFILTERTIMELEFT_H_

#include "bussiness/ITaskFilterStrategy.h"

class TaskFilterTimeLeft : public ITaskFilterStrategy
{
public:
    TaskFilterTimeLeft(std::chrono::system_clock::duration max_duration);

    std::vector<std::shared_ptr<Task>> Filter(std::shared_ptr<ITaskStorage> task_storage) override;

    std::string Description() override;

private:
    std::chrono::system_clock::duration m_MaxDuration;
};

#endif // INCLUDE_BUSSINESS_TASKFILTERTIMELEFT_H_