#ifndef INCLUDE_INFRASTRUCTURE_JSONTASKSTORAGE_H_
#define INCLUDE_INFRASTRUCTURE_JSONTASKSTORAGE_H_

#include "core/ITaskStorage.h"
#include "infrastructure/JSONTaskSerizlizer.h"
#include <unordered_map>
#include <filesystem>

class JSONTaskStorage : public ITaskStorage
{
public:
    JSONTaskStorage(JSONTaskSerializer serializer, std::filesystem::path file_path);
    ~JSONTaskStorage();

    int Add(std::shared_ptr<Task> task) override;
    std::shared_ptr<Task> Get(int id) override;
    std::vector<std::shared_ptr<Task>> Get(std::function<bool(std::shared_ptr<Task>)> predicate) override;
    std::vector<std::shared_ptr<Task>> GetAll() override;
    void Remove(int id) override;

private:
    JSONTaskSerializer m_TaskSerializer;
    std::filesystem::path m_FilePath;
    std::unordered_map<int, std::shared_ptr<Task>> m_Tasks;
    int m_NextID = 0;

    void AddRecursively(std::shared_ptr<Task> task);
};

#endif // INCLUDE_INFRASTRUCTURE_JSONTASKSTORAGE_H_