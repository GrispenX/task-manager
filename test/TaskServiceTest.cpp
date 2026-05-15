#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "infrastructure/TaskService.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

class MockTaskStorage : public ITaskStorage
{
public:
    MOCK_METHOD(int, Add, (std::shared_ptr<Task> task), (override));
    MOCK_METHOD(std::shared_ptr<Task>, Get, (int id), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Task>>, Get, (std::function<bool(std::shared_ptr<Task>)> predicate), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Task>>, GetAll, (), (override));
    MOCK_METHOD(void, Remove, (int id), (override));
};

TEST(TaskServiceTest, CreateTaskWithValidArgs)
{
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TaskService service(task_storage);

    EXPECT_CALL(*task_storage, Add(_)).Times(1).WillOnce(Return(42));

    EXPECT_EQ(service.CreateNewTask("task", std::nullopt), 42);
}

TEST(TaskServiceTest, CreateTaskWithoutNameThrowsException)
{
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TaskService service(task_storage);

    EXPECT_ANY_THROW(service.CreateNewTask("", std::nullopt));
}

TEST(TaskServiceTest, CreateTaskWithUnexistingparentThrowsException)
{
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TaskService service(task_storage);

    EXPECT_CALL(*task_storage, Get(42)).Times(1).WillOnce(Throw(std::runtime_error("Task not found")));

    EXPECT_ANY_THROW(service.CreateNewTask("task", 42));
}

TEST(TaskServiceTest, CreateTaskWithValidParent)
{
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TaskService service(task_storage);
    std::shared_ptr<Task> parent = std::make_shared<Task>(TaskOptions{.id=42, .name="parent"});

    EXPECT_CALL(*task_storage, Get(42)).Times(1).WillOnce(Return(parent));
    EXPECT_CALL(*task_storage, Add(_)).Times(1).WillOnce(Return(100));

    EXPECT_EQ(service.CreateNewTask("task", 42), 100);
    EXPECT_EQ(parent->Subtasks().size(), 1);
}

TEST(TaskServiceTest, DeleteTaskDeletesAllSubtasks)
{
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TaskService service(task_storage);
    std::shared_ptr<Task> root = std::make_shared<Task>(TaskOptions{.id=1, .name="root"});
    std::shared_ptr<Task> subtask = std::make_shared<Task>(TaskOptions{.id=2, .name="subtask"});
    root->AddSubtask(subtask);
    std::shared_ptr<Task> subsubtask = std::make_shared<Task>(TaskOptions{.id=3, .name="subsubtask"});
    subtask->AddSubtask(subsubtask);

    EXPECT_CALL(*task_storage, Get(1)).Times(1).WillOnce(Return(root));
    EXPECT_CALL(*task_storage, Remove(1)).Times(1);
    EXPECT_CALL(*task_storage, Remove(2)).Times(1);
    EXPECT_CALL(*task_storage, Remove(3)).Times(1);

    service.DeleteTask(1);
}