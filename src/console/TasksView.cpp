#include "console/TasksView.h"
#include "console/MainView.h"
#include "console/TaskDetailedView.h"
#include "console/TaskListConfigurationView.h"
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
    while(true)
    {
        std::string option_str;
        std::cout << "Option: ";
        std::getline(std::cin, option_str);
        std::istringstream ss(option_str);
        if((ss >> option) && (option >= 1 && option <= 5)) break;
        TerminalStyle::SetBackgroundColor(Red);
        TerminalStyle::SetBold();
        std::cout << "Invalid option\n";
        TerminalStyle::ResetStyle();
    }

    switch (option)
    {
    case 1:
        std::cout << "\n";
        return std::make_unique<TaskListConfigurationView>(m_Context);
        break;

    case 2: {
        std::string name;
        std::cout << "Name: ";
        std::getline(std::cin, name);
        std::string parent;

        std::cout << "Parent ID ('none' for none): ";
        std::getline(std::cin, parent);

        std::optional<int> parent_id;
        if(parent == "none")
        {
            parent_id = std::nullopt;
        }
        else
        {
            std::istringstream ss(parent);
            int parent_id;
            if(!(ss >> parent_id))
            {
                TerminalStyle::SetBackgroundColor(Red);
                TerminalStyle::SetBold();
                std::cout << "ID should be an integer\n";
                TerminalStyle::ResetStyle();
                break;
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
        std::string id_str;
        std::cout << "Task ID: ";
        std::getline(std::cin, id_str);
        std::istringstream ss(id_str);
        int id;
        if(!(ss >> id))
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "ID should be an integer\n";
            TerminalStyle::ResetStyle();
            break;
        }

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

    case 4: {
        std::string id_str;
        std::cout << "Task ID: ";
        std::getline(std::cin, id_str);
        std::istringstream ss(id_str);
        int id;
        if(!(ss >> id))
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "ID should be an integer\n";
            TerminalStyle::ResetStyle();
            break;
        }

        std::cout << "\n";
        return std::make_unique<TaskDetailedView>(m_Context, id);
        break;
    }
    
    default:
        std::cout << "\n";
        return std::make_unique<MainView>(m_Context);
        break;
    }

    std::cout << "\n";
    return std::make_unique<TasksView>(m_Context);
}