#include "bussiness/TaskFilterByTag.h"

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