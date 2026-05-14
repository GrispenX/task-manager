#include "infrastructure/TagService.h"

TagService::TagService(std::shared_ptr<ITagStorage> tag_storage, std::shared_ptr<ITaskStorage> task_storage) :
    m_TagStorage(tag_storage),
    m_TaskStorage(task_storage)
{

}

int TagService::CreateTag(std::string label, Color color)
{
    return m_TagStorage->Add(std::make_shared<Tag>(0, label, color));
}

void TagService::DeleteTag(int tag_id)
{
    std::shared_ptr<Tag> tag = m_TagStorage->Get(tag_id);
    
    for(auto task : m_TaskStorage->Get( [tag](std::shared_ptr<Task> task) { return task->HasTag(tag); } ))
    {
        task->RemoveTag(tag);
    }

    m_TagStorage->Remove(tag_id);
}

void TagService::SetTagLabel(int tag_id, std::string label)
{
    m_TagStorage->Get(tag_id)->SetLabel(label);
}

void TagService::SetTagColor(int tag_id, Color color)
{
    m_TagStorage->Get(tag_id)->SetColor(color);
}

void TagService::AddTagToTask(int task_id, int tag_id)
{
    m_TaskStorage->Get(task_id)->AddTag(m_TagStorage->Get(tag_id));
}

void TagService::RemoveTagFromTask(int task_id, int tag_id)
{
    m_TaskStorage->Get(task_id)->RemoveTag(m_TagStorage->Get(tag_id));
}