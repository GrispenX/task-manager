#include "bussiness/TaskFilterByTag.h"
#include <format>

TaskFilterByTag::TaskFilterByTag(std::shared_ptr<Tag> tag) :
    m_Tag(tag)
{

}

std::vector<std::shared_ptr<Task>> TaskFilterByTag::Filter(std::shared_ptr<ITaskStorage> storage)
{
    return storage->Get(
        [this](std::shared_ptr<Task> task) {
            return task->HasTag(m_Tag);
        }
    );
}

std::string TaskFilterByTag::Description()
{
    return std::format("By format ({})", m_Tag->GetLabel());
}