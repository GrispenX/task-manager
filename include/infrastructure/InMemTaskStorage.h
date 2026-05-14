#ifndef INCLUDE_INFRASTRUCTURE_INMEMTASKSTORAGE_H_
#define INCLUDE_INFRASTRUCTURE_INMEMTASKSTORAGE_H_

#include "core/ITaskStorage.h"
#include <unordered_map>

class InMemTaskStorage : public ITaskStorage
{
public:
    int Add(std::shared_ptr<Task> task) override;
    std::shared_ptr<Task> Get(int id) override;
    std::vector<std::shared_ptr<Task>> Get(std::function<bool(std::shared_ptr<Task>)> predicate) override;
    std::vector<std::shared_ptr<Task>> GetAll() override;
    void Remove(int id) override;

private:
    std::unordered_map<int, std::shared_ptr<Task>> m_Tasks;
    int m_NextID = 0;
};

#endif // INCLUDE_INFRASTRUCTURE_INMEMTASKSTORAGE_H_