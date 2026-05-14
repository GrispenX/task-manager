#ifndef INCLUDE_INFRASTRUCTURE_TAGSERVICE_H_
#define INCLUDE_INFRASTRUCTURE_TAGSERVICE_H_

#include "infrastructure/ITagService.h"
#include "core/ITagStorage.h"
#include "core/ITaskStorage.h"

class TagService : public ITagService
{
public:
    TagService(std::shared_ptr<ITagStorage> tag_storage, std::shared_ptr<ITaskStorage> task_storage);

    int CreateTag(std::string label, Color color) override;
    void DeleteTag(int tag_id) override;
    void SetTagLabel(int tag_id, std::string label) override;
    void SetTagColor(int tag_id, Color color) override;
    void AddTagToTask(int task_id, int tag_id) override;
    void RemoveTagFromTask(int task_id, int tag_id) override;
    std::vector<std::shared_ptr<Tag>> GetAllTags() override;

private:
    std::shared_ptr<ITagStorage> m_TagStorage;
    std::shared_ptr<ITaskStorage> m_TaskStorage;
};

#endif // INCLUDE_INFRASTRUCTURE_TAGSERVICE_H_