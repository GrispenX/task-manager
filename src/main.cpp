#include "infrastructure/JSONTagStorage.h"
#include "infrastructure/JSONTaskStorage.h"
#include "infrastructure/TaskService.h"
#include "infrastructure/TagService.h"
#include "infrastructure/TaskSelectorService.h"
#include <iostream>
#include <format>
#include "console/MainView.h"

int main()
{
    std::shared_ptr<ITagStorage> tag_storage = std::make_shared<JSONTagStorage>("tags.json");
    std::shared_ptr<ITaskStorage> task_storage = std::make_shared<JSONTaskStorage>(JSONTaskSerializer(tag_storage), "tasks.json");
    Context context {
        .task_service = std::make_shared<TaskService>(task_storage),
        .tag_service = std::make_shared<TagService>(tag_storage, task_storage),
        .task_selector_service = std::make_shared<TaskSelectorService>(task_storage)
    };

    std::unique_ptr<IView> view = std::make_unique<MainView>(context);
    while(view)
    {
        view = std::move(view->Run());
    }
}