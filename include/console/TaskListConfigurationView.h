#ifndef INCLUDE_CONSOLE_TASKLISTCONFIGURATIONVIEW_H_
#define INCLUDE_CONSOLE_TASKLISTCONFIGURATIONVIEW_H_

#include "console/IView.h"

class TaskListConfigurationView : public IView
{
public:
    TaskListConfigurationView(Context context);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;
};

#endif // INCLUDE_CONSOLE_TASKLISTCONFIGURATIONVIEW_H_