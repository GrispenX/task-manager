#ifndef INCLUDE_CONSOLE_IVIEW_H_
#define INCLUDE_CONSOLE_IVIEW_H_

#include "infrastructure/ITaskService.h"
#include "infrastructure/ITagService.h"
#include "infrastructure/ITaskSelectorService.h"
#include <memory>

struct Context
{
    std::shared_ptr<ITaskService> task_service;
    std::shared_ptr<ITagService> tag_service;
    std::shared_ptr<ITaskSelectorService> task_selector_service;
};

class IView
{
public:
    virtual ~IView() = default;

    virtual std::unique_ptr<IView> Run() = 0;
};

#endif // INCLUDE_CONSOLE_IVIEW_H_