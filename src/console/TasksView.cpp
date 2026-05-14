#include "console/TasksView.h"
#include "console/MainView.h"
#include "console/TaskDetailedView.h"

#include "console/TerminalStyle.h"
#include <iostream>

TasksView::TasksView(Context context) :
    m_Context(context)
{

}

std::unique_ptr<IView> TasksView::Run()
{
    TerminalStyle::ResetStyle();
    std::cout << "===== Tasks =====\n";
    std::cout << "Choose the option:\n";
    std::cout << "  1. List\n";
    std::cout << "  2. Create\n";
    std::cout << "  3. Delete\n";
    std::cout << "  4. Details\n";
    std::cout << "  5. Back\n";

    int option = 0;
    do
    {
        std::string option_str;
        std::cout << "Option: ";
        std::cin >> option_str;
        try
        {
            option = std::stoi(option_str);
        }
        catch(const std::exception& e)
        {
            option = 0;
        }
        
    } while (option < 1 || option > 5);

    switch (option)
    {
    case 1:
        break;

    case 2: {
        std::string name;
        std::cout << "Name: ";
        std::getline(std::cin, name);
        std::string parent;
        std::cout << "Parent ID (- for none): ";
        std::cin >> parent;
        std::optional<int> parent_id;

        if(parent == "-")
        {
            parent_id = std::nullopt;
        }
        else
        {
            try
            {
                parent_id = std::stoi(parent);
            }
            catch(const std::exception& e)
            {
                TerminalStyle::SetBackgroundColor(Red);
                TerminalStyle::SetBold();
                std::cout << "ID should be an integer\n";
                TerminalStyle::ResetStyle();
            }
        }

        try
        {
            int id = m_Context.task_service->CreateNewTask(name, parent_id);
            std::cout << "\n";
            return std::make_unique<TaskDetailedView>(m_Context, id);
        }
        catch(const std::exception& e)
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << e.what() << "\n";
            TerminalStyle::ResetStyle();
        }
        break;
    }

    case 3: {
        int id;
        std::cout << "Task ID: ";
        std::cin >> id;
        try
        {
            m_Context.task_service->DeleteTask(id);
        }
        catch(const std::exception& e)
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << e.what() << "\n";
            TerminalStyle::ResetStyle();
        }
        break;
    }

    case 4:
        int id;
        std::cout << "Task ID: ";
        std::cin >> id;
        std::cout << "\n";
        return std::make_unique<TaskDetailedView>(m_Context, id);
        break;
    
    default:
        std::cout << "\n";
        return std::make_unique<MainView>(m_Context);
        break;
    }

    std::cout << "\n";
    return std::make_unique<TasksView>(m_Context);
}