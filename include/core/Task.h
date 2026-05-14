#ifndef INCLUDE_CORE_TASK_H_
#define INCLUDE_CORE_TASK_H_

#include "core/Tag.h"
#include <string>
#include <chrono>
#include <optional>
#include <memory>
#include <vector>

struct TaskOptions
{
    int id = 0;
    std::string name;
    std::string description;
    bool is_done = false;
    std::optional<std::chrono::system_clock::time_point> deadline = std::nullopt;
};

class Task : public std::enable_shared_from_this<Task>
{
public:
    Task(TaskOptions options);

    int ID() const;
    std::string Name() const;
    std::string Description() const;
    bool IsDone() const;
    std::optional<std::chrono::system_clock::time_point> Deadline() const;
    std::vector<std::shared_ptr<Task>> Subtasks() const;
    std::weak_ptr<Task> ParentTask() const;
    std::vector<std::shared_ptr<Tag>> Tags();

    void SetID(int id);
    void SetName(std::string name);
    void SetDescription(std::string description);
    void SetDone(bool is_done);
    void SetDeadline(std::optional<std::chrono::system_clock::time_point> deadline);

    void AddSubtask(std::shared_ptr<Task> task);
    void RemoveSubtask(std::shared_ptr<Task> task);

    void AddTag(std::shared_ptr<Tag> tag);
    void RemoveTag(std::shared_ptr<Tag> tag);
    bool HasTag(std::shared_ptr<Tag> tag);

private:
    int m_ID;
    std::string m_Name;
    std::string m_Description;
    bool m_IsDone;
    std::optional<std::chrono::system_clock::time_point> m_Deadline;
    std::vector<std::shared_ptr<Task>> m_Subtasks;
    std::weak_ptr<Task> m_ParentTask;
    std::vector<std::shared_ptr<Tag>> m_Tags;
};

#endif // INCLUDE_CORE_TASK_H_