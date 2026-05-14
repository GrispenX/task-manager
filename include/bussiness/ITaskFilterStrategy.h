#ifndef INCLUDE_BUSSINESS_ITASKFILTERSTRATEGY_H_
#define INCLUDE_BUSSINESS_ITASKFILTERSTRATEGY_H_

#include "core/Task.h"
#include "core/ITaskStorage.h"
#include <vector>
#include <memory>

class ITaskFilterStrategy
{
public:
    virtual ~ITaskFilterStrategy() = default;

    virtual std::vector<std::shared_ptr<Task>> Filter(std::shared_ptr<ITaskStorage> task_storage) = 0;
};

#endif // INCLUDE_BUSSINESS_ITASKFILTERSTRATEGY_H_