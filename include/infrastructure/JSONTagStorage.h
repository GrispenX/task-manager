#ifndef INCLUDE_INFRASTRUCTURE_JSONTAGSTORAGE_H_
#define INCLUDE_INFRASTRUCTURE_JSONTAGSTORAGE_H_

#include "core/ITagStorage.h"
#include "infrastructure/JSONTagSerializer.h"
#include <unordered_map>
#include <filesystem>

class JSONTagStorage : public ITagStorage
{
public:
    JSONTagStorage(std::filesystem::path file_path);
    ~JSONTagStorage();

    int Add(std::shared_ptr<Tag> tag) override;
    std::shared_ptr<Tag> Get(int id) override;
    std::vector<std::shared_ptr<Tag>> GetAll() override;
    void Remove(int id) override;

private:
    JSONTagSerializer m_TagSerializer;
    std::filesystem::path m_FilePath;
    std::unordered_map<int, std::shared_ptr<Tag>> m_Tags;
    int m_NextID = 1;
};

#endif // INCLUDE_INFRASTRUCTURE_JSONTAGSTORAGE_H_