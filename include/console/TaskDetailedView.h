#ifndef INCLUDE_CONSOLE_TASKDETAILEDVIEW_H_
#define INCLUDE_CONSOLE_TASKDETAILEDVIEW_H_

#include "console/IView.h"

class TaskDetailedView : public IView
{
public:
    TaskDetailedView(Context context, int task_id);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;
    int m_ID;
};

#endif // INCLUDE_CONSOLE_TASKDETAILEDVIEW_H_