#include "console/TaskDetailedView.h"
#include "console/TasksView.h"
#include "console/TerminalStyle.h"
#include <iostream>
#include <format>

TaskDetailedView::TaskDetailedView(Context context, int task_id) :
    m_Context(context),
    m_ID(task_id)
{

}

std::unique_ptr<IView> TaskDetailedView::Run()
{
    auto task_opt = m_Context.task_service->GetTask(m_ID);
    if(!task_opt)
    {
        TerminalStyle::SetBackgroundColor(Red);
        TerminalStyle::SetBold();
        std::cout << "Task not found\n";
        TerminalStyle::ResetStyle();
        std::cout << "\n";
        return std::make_unique<TasksView>(m_Context);
    }

    std::shared_ptr<Task> task = task_opt.value();

    int id = task->ID();
    std::string name = task->Name();
    std::string description = task->Description();
    bool is_done = task->IsDone();
    std::optional<std::chrono::system_clock::time_point> deadline = task->Deadline();
    std::vector<std::shared_ptr<Tag>> tags = task->Tags();
    std::shared_ptr<Task> parent = task->ParentTask().lock();
    std::vector<std::shared_ptr<Task>> subtasks = task->Subtasks();

    std::cout << "===== Task =====\n";
    std::cout << std::format("ID: {}\n", id);
    std::cout << std::format("Name: {}\n", name);
    std::cout << std::format("Description: {}\n", description.empty() ? "None" : description);
    std::cout << std::format("Done: {}\n", is_done ? "Yes" : "No");
    std::cout << std::format("Deadline: {}\n",deadline.has_value() ? std::format("{:%Y-%m-%d %H:%M:%S}", deadline.value()) : "None");

    std::cout << "Tags: ";
    if(tags.empty())
    {
        std::cout << "None\n";
    }
    else
    {
        for(auto tag : task->Tags())
        {
            TerminalStyle::SetBackgroundColor(tag->GetColor());
            std::cout << "  ";
            TerminalStyle::ResetStyle();
            std::cout << std::format(" {}. {} ", tag->GetID(), tag->GetLabel());
        }
        std::cout << "\n";
    }

    std::cout << "Parent ID: ";
    if(parent)
    {
        std::cout << parent->ID() << "\n";
    }
    else
    {
        std::cout << "None\n";
    }

    std::cout << "Subtask ID's: ";
    if(subtasks.empty())
    {
        std::cout << "None\n";
    }
    else 
    {
        for(auto subtask : subtasks)
        {
            std::cout << subtask->ID() << ", ";
        }
        std::cout << "\n";
    }



    std::cout << "\n";
    std::cout << "Choose the option:\n";
    std::cout << "  1. Change name\n";
    std::cout << "  2. Change description\n";
    std::cout << "  3. Switch status\n";
    std::cout << "  4. Change deadline\n";
    std::cout << "  5. Add tag\n";
    std::cout << "  6. Remove tag\n";
    std::cout << "  7. Back\n";
    std::cout << "\n";

    int option = 0;
    do
    {
        std::cout << "Option: ";
        std::cin >> option;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (option < 1 || option > 7);

    switch (option)
    {
    case 1: {
        std::string new_name;
        std::cout << "New name: ";
        std::getline(std::cin, new_name);
        m_Context.task_service->SetTaskName(m_ID, new_name);
        break;
    }

    case 2: {
        std::string new_desc;
        std::cout << "New description: ";
        std::getline(std::cin, new_desc);
        m_Context.task_service->SetTaskDescription(m_ID, new_desc);
        break;
    }

    case 3:
        m_Context.task_service->SwitchTaskStatus(m_ID);
        break;

    case 4: {
        std::string deadline_str;
        std::cout << "New deadline (YYYY-MM-DD HH:MM:SS): ";
        std::getline(std::cin, deadline_str);

        std::tm tm = {};
        std::istringstream iss(deadline_str);
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if(iss.fail())
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "Invalid format\n";
            TerminalStyle::ResetStyle();
            break;
        }
        std::time_t time = std::mktime(&tm);
        std::chrono::system_clock::time_point new_deadline = std::chrono::system_clock::from_time_t(time);

        m_Context.task_service->SetTaskDeadline(m_ID, new_deadline);
        break;
    }

    case 5: {
        int tag_id;
        std::cout << "Tag ID: ";
        std::cin >> tag_id;
        try
        {
            m_Context.tag_service->AddTagToTask(m_ID, tag_id);
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

    case 6: {
        int tag_id;
        std::cout << "Tag ID: ";
        std::cin >> tag_id;
        try
        {
            m_Context.tag_service->RemoveTagFromTask(m_ID, tag_id);
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
    
    default:
        std::cout << "\n";
        return std::make_unique<TasksView>(m_Context);
        break;
    }

    std::cout << "\n";
    return std::make_unique<TaskDetailedView>(m_Context, m_ID);
}