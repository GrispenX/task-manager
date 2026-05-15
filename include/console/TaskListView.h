#ifndef INCLUDE_CONSOLE_TASKLISTVIEW_H_
#define INCLUDE_CONSOLE_TASKLISTVIEW_H_

#include "console/IView.h"

class TaskListView : public IView
{
public:
    TaskListView(Context context);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;
};

#endif // INCLUDE_CONSOLE_TASKLISTVIEW_H_