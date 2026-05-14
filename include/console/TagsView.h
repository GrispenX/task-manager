#ifndef INCLUDE_CONSOLE_TAGSVIEW_H_
#define INCLUDE_CONSOLE_TAGSVIEW_H_

#include "console/IView.h"

class TagsView : public IView
{
public:
    TagsView(Context context);

    std::unique_ptr<IView> Run() override;

private:
    Context m_Context;
};

#endif // INCLUDE_CONSOLE_TAGSVIEW_H_