#include "console/MainView.h"
#include "console/TasksView.h"
#include "console/TagsView.h"
#include "console/TerminalStyle.h"
#include <iostream>

MainView::MainView(Context context) :
    m_Context(context)
{

}

std::unique_ptr<IView> MainView::Run()
{
    TerminalStyle::ResetStyle();
    std::cout << "===== Task Manager =====\n";
    std::cout << "Choose the option:\n";
    std::cout << "  1. Tasks\n";
    std::cout << "  2. Tags\n";
    std::cout << "  3. Quit\n";
    std::cout << "\n";

    int option = 0;
    do
    {
        std::cout << "Option: ";
        std::cin >> option;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (option < 1 || option > 3);
    
    std::cout << "\n";
    switch (option)
    {
    case 1:
        return std::make_unique<TasksView>(m_Context);
        break;

    case 2:
        return std::make_unique<TagsView>(m_Context);
        break;
    
    default:
        return nullptr;
        break;
    }
}