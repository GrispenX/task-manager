#include "bussiness/TaskFilterTimeLeft.h"
#include <format>

TaskFilterTimeLeft::TaskFilterTimeLeft(std::chrono::system_clock::duration max_duration) :
    m_MaxDuration(max_duration)
{

}

std::vector<std::shared_ptr<Task>> TaskFilterTimeLeft::Filter(std::shared_ptr<ITaskStorage> storage)
{
    auto from = std::chrono::system_clock::now();
    auto to = from + m_MaxDuration;
    return storage->Get(
        [from, to](std::shared_ptr<Task> task) {
            if(task->IsDone()) return false;
            auto deadline = task->Deadline();
            if(!deadline) return false;
            return deadline.value() >= from && deadline.value() <= to;
        }
    );
}

std::string TaskFilterTimeLeft::Description()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    return std::format("Tasks from now to {:%Y-%m-%d %H:%M:%S}", now + m_MaxDuration);
}