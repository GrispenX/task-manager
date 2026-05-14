#ifndef INCLUDE_INFRASTRUCTURE_INMEMTAGSTORAGE_H_
#define INCLUDE_INFRASTRUCTURE_INMEMTAGSTORAGE_H_

#include "core/ITagStorage.h"
#include <unordered_map>

class InMemTagStorage : public ITagStorage
{
public:
    int Add(std::shared_ptr<Tag> tag) override;
    std::shared_ptr<Tag> Get(int id) override;
    std::vector<std::shared_ptr<Tag>> GetAll() override;
    void Remove(int id) override;

private:
    std::unordered_map<int, std::shared_ptr<Tag>> m_Tags;
    int m_NextID = 0;
};

#endif // INCLUDE_INFRASTRUCTURE_INMEMTAGSTORAGE_H_