#ifndef INCLUDE_CONSOLE_TASKSVIEW_H_
#define INCLUDE_CONSOLE_TASKSVIEW_H_

#include "console/IView.h"

class TasksView : public IView
{
public:
    TasksView(Context context);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;
};

#endif // INCLUDE_CONSOLE_TASKSVIEW_H_