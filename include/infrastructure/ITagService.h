#ifndef INCLUDE_INFRASTRUCTURE_ITAGSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_ITAGSERVICE_H_

#include "core/Tag.h"
#include <vector>
#include <memory>
#include <optional>

class ITagService
{
public:
    virtual ~ITagService() = default;

    virtual int CreateTag(std::string label, Color color) = 0;
    virtual void DeleteTag(int tag_id) = 0;
    virtual void SetTagLabel(int tag_id, std::string label) = 0;
    virtual void SetTagColor(int tag_id, Color color) = 0;
    virtual void AddTagToTask(int task_id, int tag_id) = 0;
    virtual void RemoveTagFromTask(int task_id, int tag_id) = 0;
    virtual std::optional<std::shared_ptr<Tag>> GetTag(int tag_id) = 0;
    virtual std::vector<std::shared_ptr<Tag>> GetAllTags() = 0;
};

#endif // INCLUDE_INFRASTRUCTURE_ITAGSERVICE_H_