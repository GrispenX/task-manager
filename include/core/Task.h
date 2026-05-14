#ifndef INCLUDE_CORE_TASK_H_
#define INCLUDE_CORE_TASK_H_

#include <string>
#include <chrono>
#include <optional>
#include <memory>
#include <vector>

class Task : public std::enable_shared_from_this<Task>
{
public:
    Task(
        std::string name,
        std::string description,
        bool is_done,
        int id = 0,
        std::optional<std::chrono::time_point<std::chrono::system_clock>> deadline = std::nullopt
    );

    int ID() const;
    std::string Name() const;
    std::string Description() const;
    bool IsDone() const;
    std::optional<std::chrono::time_point<std::chrono::system_clock>> Deadline() const;
    std::vector<std::shared_ptr<Task>> Subtasks() const;
    std::weak_ptr<Task> ParentTask() const;

    void SetID(int id);
    void SetName(std::string name);
    void SetDescription(std::string description);
    void SetDone(bool is_done);
    void SetDeadline(std::optional<std::chrono::time_point<std::chrono::system_clock>> deadline);

    void AddSubtask(std::shared_ptr<Task> task);

private:
    int m_ID;
    std::string m_Name;
    std::string m_Description;
    bool m_IsDone;
    std::optional<std::chrono::time_point<std::chrono::system_clock>> m_Deadline;
    std::vector<std::shared_ptr<Task>> m_Subtasks;
    std::weak_ptr<Task> m_ParentTask;
};

#endif // INCLUDE_CORE_TASK_H_