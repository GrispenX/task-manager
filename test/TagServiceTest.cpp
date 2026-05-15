#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "infrastructure/TagService.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::An;

class MockTagStorage : public ITagStorage
{
public:
    MOCK_METHOD(int, Add, (std::shared_ptr<Tag> tag), (override));
    MOCK_METHOD(std::shared_ptr<Tag>, Get, (int id), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Tag>>, GetAll, (), (override));
    MOCK_METHOD(void, Remove, (int id), (override));
};

class MockTaskStorage : public ITaskStorage
{
public:
    MOCK_METHOD(int, Add, (std::shared_ptr<Task> task), (override));
    MOCK_METHOD(std::shared_ptr<Task>, Get, (int id), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Task>>, Get, (std::function<bool(std::shared_ptr<Task>)> predicate), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Task>>, GetAll, (), (override));
    MOCK_METHOD(void, Remove, (int id), (override));
};

TEST(TagServiceTest, RemoveTagRemovesTagFromTasks)
{
    std::shared_ptr<MockTagStorage> tag_storage = std::make_shared<MockTagStorage>();
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TagService service(tag_storage, task_storage);

    std::shared_ptr<Tag> tag = std::make_shared<Tag>(42, "tag", Red);
    std::shared_ptr<Task> task1 = std::make_shared<Task>(TaskOptions{.name = "task 1"});
    std::shared_ptr<Task> task2 = std::make_shared<Task>(TaskOptions{.name = "task 2"});
    std::vector<std::shared_ptr<Task>> tasks {task1, task2};
    task1->AddTag(tag);
    task2->AddTag(tag);

    EXPECT_CALL(*tag_storage, Get(42)).Times(1).WillOnce(Return(tag));
    EXPECT_CALL(*task_storage, Get(An<std::function<bool(std::shared_ptr<Task>)>>())).Times(1).WillOnce(Return(tasks));
    EXPECT_CALL(*tag_storage, Remove(42)).Times(1);

    service.DeleteTag(42);

    EXPECT_FALSE(task1->HasTag(tag) && task2->HasTag(tag));
}

TEST(TagServiceTest, AddTagToTaskAddsTagToTask)
{
    std::shared_ptr<MockTagStorage> tag_storage = std::make_shared<MockTagStorage>();
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TagService service(tag_storage, task_storage);

    std::shared_ptr<Tag> tag = std::make_shared<Tag>(42, "tag", Red);
    std::shared_ptr<Task> task = std::make_shared<Task>(TaskOptions{.id = 12, .name = "task"});
    task->AddTag(tag);

    EXPECT_CALL(*tag_storage, Get(42)).Times(1).WillOnce(Return(tag));
    EXPECT_CALL(*task_storage, Get(12)).Times(1).WillOnce(Return(task));

    service.AddTagToTask(12, 42);

    EXPECT_TRUE(task->HasTag(tag));
}

TEST(TagServiceTest, AddTagToUnexistingTaskThrowsException)
{
    std::shared_ptr<MockTagStorage> tag_storage = std::make_shared<MockTagStorage>();
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TagService service(tag_storage, task_storage);

    std::shared_ptr<Tag> tag = std::make_shared<Tag>(42, "tag", Red);

    ON_CALL(*tag_storage, Get(42)).WillByDefault(Return(tag));
    EXPECT_CALL(*task_storage, Get(12)).WillOnce(Throw(std::runtime_error("Task not found")));

    EXPECT_ANY_THROW(service.AddTagToTask(12, 42));
}

TEST(TagServiceTest, AddUnexistingTagToTaskThrowsException)
{
    std::shared_ptr<MockTagStorage> tag_storage = std::make_shared<MockTagStorage>();
    std::shared_ptr<MockTaskStorage> task_storage = std::make_shared<MockTaskStorage>();
    TagService service(tag_storage, task_storage);

    std::shared_ptr<Task> task = std::make_shared<Task>(TaskOptions{.id = 12, .name = "task"});

    EXPECT_CALL(*tag_storage, Get(42)).Times(1).WillOnce(Throw(std::runtime_error("Tag not found")));
    ON_CALL(*task_storage, Get(12)).WillByDefault(Return(task));

    EXPECT_ANY_THROW(service.AddTagToTask(12, 42));
}