#ifndef INCLUDE_CORE_ITASKSTORAGE_H_
#define INCLUDE_CORE_ITASKSTORAGE_H_

#include "core/Task.h"
#include <memory>
#include <vector>
#include <functional>

class ITaskStorage
{
public:
    virtual ~ITaskStorage() = default;

    virtual int Add(std::shared_ptr<Task> task) = 0;
    virtual std::shared_ptr<Task> Get(int id) = 0;
    virtual std::vector<std::shared_ptr<Task>> Get(std::function<bool(std::shared_ptr<Task>)> predicate) = 0;
    virtual std::vector<std::shared_ptr<Task>> GetAll() = 0;
    virtual void Remove(int id) = 0;
};

#endif // INCLUDE_CORE_ITASKSTORAGE_H_