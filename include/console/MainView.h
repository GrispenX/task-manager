#ifndef INCLUDE_CONSOLE_MAINVIEW_H_
#define INCLUDE_CONSOLE_MAINVIEW_H_

#include "console/IView.h"

class MainView : public IView
{
public:
    MainView(Context context);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;
};

#endif // INCLUDE_CONSOLE_MAINVIEW_H_