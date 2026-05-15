#include "console/TaskListConfigurationView.h"
#include "console/TasksView.h"
#include "console/TaskListView.h"

#include "bussiness/TaskFilterByTag.h"
#include "bussiness/TaskFilterMissed.h"
#include "bussiness/TaskFilterNoDeadline.h"
#include "bussiness/TaskFilterTimeLeft.h"

#include "console/TerminalStyle.h"
#include <iostream>
#include <format>

TaskListConfigurationView::TaskListConfigurationView(Context context) :
    m_Context(context)
{

}

std::unique_ptr<IView> TaskListConfigurationView::Run()
{
    std::shared_ptr<ITaskFilterStrategy> task_filter = m_Context.task_selector_service->GetFilterStrategy();

    std::cout << "===== Task List Configuration =====\n";
    std::cout << "Filter: " << (task_filter != nullptr ? task_filter->Description() : "None") << "\n";
    std::cout << "\n";
    std::cout << "Choose the option:\n";
    std::cout << "  1. Set filter by tag\n";
    std::cout << "  2. Set filter on missed tasks\n";
    std::cout << "  3. Set filter on tasks w\\o deadline\n";
    std::cout << "  4. Set filter by time left\n";
    std::cout << "  5. Remove filter\n";
    std::cout << "  6. List\n";
    std::cout << "  7. Back\n";
    std::cout << "\n";

    int option = 0;
    while(true)
    {
        std::string option_str;
        std::cout << "Option: ";
        std::getline(std::cin, option_str);
        std::istringstream ss(option_str);
        if((ss >> option) && (option >= 1 && option <= 7)) break;
        TerminalStyle::SetBackgroundColor(Red);
        TerminalStyle::SetBold();
        std::cout << "Invalid option\n";
        TerminalStyle::ResetStyle();
    }

    switch (option)
    {
    case 1: {
        std::string tag_id_str;
        std::cout << "Tag ID: ";
        std::getline(std::cin, tag_id_str);
        std::istringstream ss(tag_id_str);
        int tag_id;
        if(!(ss >> tag_id))
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "Tag ID should be an integer\n";
            TerminalStyle::ResetStyle();
            break;
        }

        std::optional<std::shared_ptr<Tag>> tag = m_Context.tag_service->GetTag(tag_id);
        if(tag.has_value())
        {
            m_Context.task_selector_service->SetFilterStrategy(std::make_shared<TaskFilterByTag>(tag.value()));
        }
        else
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "Tag not found\n";
            TerminalStyle::ResetStyle();
        }
        break;
    }

    case 2: 
        m_Context.task_selector_service->SetFilterStrategy(std::make_shared<TaskFilterMissed>());
        break;

    case 3: 
        m_Context.task_selector_service->SetFilterStrategy(std::make_shared<TaskFilterNoDeadline>());
        break;

    case 4: {
        std::string days_str;
        std::cout << "Duration in days: ";
        std::getline(std::cin, days_str);
        std::istringstream ss(days_str);
        int days;
        if(!(ss >> days))
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "Duration should be an integer\n";
            TerminalStyle::ResetStyle();
        }

        m_Context.task_selector_service->SetFilterStrategy(std::make_shared<TaskFilterTimeLeft>(std::chrono::days(days)));
        break;
    }

    case 5:
        m_Context.task_selector_service->SetFilterStrategy(nullptr);
        break;

    case 6:
        std::cout << "\n";
        return std::make_unique<TaskListView>(m_Context);
        break;
    
    default:
        std::cout << "\n";
        return std::make_unique<TasksView>(m_Context);
        break;
    }

    std::cout << "\n";
    return std::make_unique<TaskListConfigurationView>(m_Context);
}