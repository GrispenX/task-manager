# Task Manager

Простий CLI менеджер завдань для роботи з деревоподібною структурою завдань. В ньому є підтримка тегів, 4 види фільтрації: за тегом, пропущені, без дедлайну, незабаром дедлайн.

## Build & run

Необхідно встановити:

- C++ компілятор (g++, clang, MSVC, etc) з 20 стандартом

- CMake

- nlohmann/json

Build:

```bash
mkdir build
cd build
cmake ..
make
```

Run:

```bash
./build/src/TaskManager
```

Run tests:

```bash
./build/test/TaskManagerTest
```

## Архітектура

```mermaid
classDiagram
direction TB
    class TaskSerializer {
	    +json Serialize(Task task)
	    +Task Deserialize(json task_json)
    }

    class ITaskStorage {
	    +int Add(Task task)
	    +Task Get(int id)
	    +Task[] Get(predicate)
	    +Task[] GetAll()
	    +void Remove(int id)
    }

    class Tag {
	    -int m_ID ~get/set~
	    -string m_Laber ~get/set~
	    -Color m_Color ~get/set~
    }

    class Color {
	    -int m_R ~get/set~
	    -int m_G ~get/set~
	    -int m_B ~get/set~
    }

    class Task {
	    -int m_ID ~get/set~
	    -string m_Name ~get/set~
	    -string m_Description ~get/set~
	    -bool m_IsDone ~get/set~
	    -optional~time_point~ m_Deadline ~get/set~
	    -Task[] m_Subtasks
	    -Task m_Parent ~get~
	    Tag[] m_Tags ~get~
	    +void AddSubtask(Task task)
	    +void RemoveSubtask(Task task)
	    +void AddTag(Tag tag)
	    +void RemoveTag(Tag tag)
	    +bool HasTag(Tag tag)
    }

    class ITagStorage {
	    +int Add(Tag tag)
	    +Tag Get(int id)
	    +Tag[] GetAll()
	    +void Remove(Tag tag)
    }

    class ITaskSelectorService {
	    +void SetFilterStrategy(ITaskFilterStrategy filter)
	    +ITaskFilterStrategy GetFilterStrategy()
	    +Task[] GetTasks()
    }

    class ITagService {
	    +int CreateTag(Tag tag)
	    +void DeleteTag(int tag_id)
	    +void SetTagLabel(int tag_id, string label)
	    +void SetTagColor(int tag_id, Color color)
	    +void AddTagToTask(int task_id, int tag_id)
	    +void RemoveTagFromTask(int task_id, int tag_id)
	    +optional~Tag~ GetTag(int tag_id)
	    +Tag[] GetAllTags()
    }

    class TagService {
	    -ITagStorage m_TagStorage
	    -ITaskStorage m_TaskStorage
	    +int CreateTag(Tag tag)
	    +void DeleteTag(int tag_id)
	    +void SetTagLabel(int tag_id, string label)
	    +void SetTagColor(int tag_id, Color color)
	    +void AddTagToTask(int task_id, int tag_id)
	    +void RemoveTagFromTask(int task_id, int tag_id)
	    +optional~Tag~ GetTag(int tag_id)
	    +Tag[] GetAllTags()
    }

    class TaskSelectorService {
	    -ITaskStorage m_TaskStorage
	    -ITaskFilterStrategy m_TaskFilter
	    +void SetFilterStrategy(ITaskFilterStrategy filter)
	    +ITaskFilterStrategy GetFilterStrategy()
	    +Task[] GetTasks()
    }

    class ITaskFilterStrategy {
	    +Task[] Filter(ITaskStorage task_storage)
	    +string Description()
    }

    class TaskFilterByTag {
	    -Tag m_Tag
	    +Task[] Filter(ITaskStorage task_storage)
	    +string Description()
    }

    class TaskFilterMissed {
	    +Task[] Filter(ITaskStorage task_storage)
	    +string Description()
    }

    class TaskFilterNoDeadline {
	    +Task[] Filter(ITaskStorage task_storage)
	    +string Description()
    }

    class TaskFilterTimeLeft {
	    -duration m_MaxDuration
	    +Task[] Filter(ITaskStorage task_storage)
	    +string Description()
    }

    class JSONTagStorage {
	    -JSONTagSerializer m_Serializer
	    -filesystem::path m_FilePath
	    -unordered_map~Tag~ m_Tags
	    -int m_DextID
	    +int Add(Tag tag)
	    +Tag Get(int id)
	    +Tag[] GetAll()
	    +void Remove(Tag tag)
    }

    class TaskJSONStorage {
	    -TaskSerializer m_Serializer
	    -filesystem::path m_FilePath
	    -unordered_map~Task~ m_Tasks
	    -int m_NextID
	    +int Add(Task task)
	    +void Update(Task task)
	    +Task Get(int id)
	    +Task[] Get(predicate)
	    +Task[] GetAll()
    }

    class ITaskService {
	    +int CreateNewTask(string name, int parent_id)
	    +void SwitchTaskStatus(int tast_id)
	    +void DeleteTask(int task_id)
	    +void SetTaskName(int task_id, string name)
	    +void SetTaskDescription(int task_id, string description)
	    +void SetTaskDeadline(int task_id, time_point deadline)
	    +void RemoveTaskDeadline(int task_id)
	    +optional~Task~ GetTask(int task_id)
	    +Task[] GetOrphanTasks()
    }

    class TaskService {
	    -ITaskStorage m_TaskStorage
	    +int CreateNewTask(string name, int parent_id)
	    +void SwitchTaskStatus(int tast_id)
	    +void DeleteTask(int task_id)
	    +void SetTaskName(int task_id, string name)
	    +void SetTaskDescription(int task_id, string description)
	    +void SetTaskDeadline(int task_id, time_point deadline)
	    +void RemoveTaskDeadline(int task_id)
	    +optional~Task~ GetTask(int task_id)
	    +Task[] GetOrphanTasks()
    }

    class JSONTagSerializer {
	    +json Serialize(Tag tag)
	    +Tag Deserialize(json tag_json)
    }

	<<Interface>> ITaskStorage
	<<Interface>> ITagStorage
	<<Interface>> ITaskSelectorService
	<<Interface>> ITagService
	<<Intefrace>> ITaskFilterStrategy
	<<Intefrace>> TaskFilterTimeLeft
	<<Interface>> ITaskService

    ITaskStorage <|.. TaskJSONStorage
    TaskJSONStorage --* TaskSerializer
    TaskJSONStorage --* Task
    ITaskService <|.. TaskService
    TaskService --o ITaskStorage
    Tag --* Color
    ITagService <|.. TagService
    ITaskSelectorService <|.. TaskSelectorService
    ITaskFilterStrategy <|.. TaskFilterByTag
    ITaskFilterStrategy <|.. TaskFilterMissed
    ITaskFilterStrategy <|.. TaskFilterNoDeadline
    ITaskFilterStrategy <|.. TaskFilterTimeLeft
    TaskSelectorService --o ITaskFilterStrategy
    Task --* Tag
    ITagStorage <|.. JSONTagStorage
    TagService --o ITaskStorage
    TagService --o ITagStorage
    TaskSelectorService --o ITaskStorage
    JSONTagStorage --* Tag
    JSONTagStorage --* JSONTagSerializer
```

## Структура

```
task-manager
├── include
│   ├── bussiness
│   ├── console
│   ├── core
│   └── infrastructure
├── src
│   ├── bussiness
│   ├── console
│   ├── core
│   └── infrastructure
└── test
```

- `include/` містить хедери (.h)

- `src/` містить реалізацію (.cpp)

- `test/` містить unit-тести

- `core/` містить доменні сутності (Color, Tag, Task), базові контракти репозиторіїв

- `bussiness/` містить бізнес-правила (фільтрація тасок)

- `infrastructure/` містить сервіси та реалізації репозиторіїв

- `console/` містить UI (CLI)