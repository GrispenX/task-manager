#ifndef INCLUDE_CORE_ITAGSTORAGE_H_
#define INCLUDE_CORE_ITAGSTORAGE_H_

#include "core/Tag.h"
#include <memory>
#include <vector>

class ITagStorage
{
public:
    virtual ~ITagStorage() = default;

    virtual int Add(std::shared_ptr<Tag> tag) = 0;
    virtual std::shared_ptr<Tag> Get(int id) = 0;
    virtual std::vector<std::shared_ptr<Tag>> GetAll() = 0;
    virtual void Remove(int id) = 0;
};

#endif // INCLUDE_CORE_ITAGSTORAGE_H_