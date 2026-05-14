#include "bussiness/TaskFilterNoDeadline.h"

std::vector<std::shared_ptr<Task>> TaskFilterNoDeadline::Filter(std::shared_ptr<ITaskStorage> storage)
{
    return storage->Get(
        [](std::shared_ptr<Task> task) {
            return !task->Deadline().has_value();
        }
    );
}