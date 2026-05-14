#ifndef INCLUDE_BUSSINESS_TASKFILTERBYTAG_H_
#define INCLUDE_BUSSINESS_TASKFILTERBYTAG_H_

#include "bussiness/ITaskFilterStrategy.h"

class TaskFilterByTag : public ITaskFilterStrategy
{
public:
    TaskFilterByTag(std::shared_ptr<Tag> tag);

    std::vector<std::shared_ptr<Task>> Filter(std::shared_ptr<ITaskStorage> task_storage) override;

private:
    std::shared_ptr<Tag> m_Tag;
};

#endif // INCLUDE_BUSSINESS_TASKFILTERBYTAG_H_