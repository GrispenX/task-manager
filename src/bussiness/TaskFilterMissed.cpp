#include "bussiness/TaskFilterMissed.h"

std::vector<std::shared_ptr<Task>> TaskFilterMissed::Filter(std::shared_ptr<ITaskStorage> task_storage)
{
    auto now = std::chrono::system_clock::now();
    return task_storage->Get(
        [now](std::shared_ptr<Task> task) {
            auto deadline = task->Deadline();
            if(!deadline) return false;
            return task->IsDone() == false && deadline.value() < now;
        }
    );
}