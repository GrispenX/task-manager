#ifndef INCLUDE_CONSOLE_TASKTREEVIEW_H_
#define INCLUDE_CONSOLE_TASKTREEVIEW_H_

#include "console/IView.h"

class TaskTreeView : public IView
{
public:
    TaskTreeView(Context context);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;

    void PrintTaskRecursively(std::shared_ptr<Task> task, std::string prefix = "");
};

#endif // INCLUDE_CONSOLE_TASKTREEVIEW_H_