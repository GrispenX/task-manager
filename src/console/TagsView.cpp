#include "console/TagsView.h"
#include "console/MainView.h"
#include "console/TerminalStyle.h"
#include <iostream>

TagsView::TagsView(Context context) :
    m_Context(context)
{

}

std::unique_ptr<IView> TagsView::Run()
{
    TerminalStyle::ResetStyle();
    std::cout << "===== Tags =====\n";
    std::cout << "Choose the option\n";
    std::cout << "  1. List\n";
    std::cout << "  2. Create\n";
    std::cout << "  3. Delete\n";
    std::cout << "  4. Back\n";
    std::cout << "\n";

    int option = 0;
    while(true)
    {
        std::string option_str;
        std::cout << "Option: ";
        std::getline(std::cin, option_str);
        std::istringstream ss(option_str);
        if((ss >> option) && (option >= 1 && option <= 4)) break;
        TerminalStyle::SetBackgroundColor(Red);
        TerminalStyle::SetBold();
        std::cout << "Invalid option";
        TerminalStyle::ResetStyle();
        std::cout << "\n";
    }

    switch (option)
    {
    case 1:
        std::cout << "===== Tags List =====\n";
        for(auto tag : m_Context.tag_service->GetAllTags())
        {
            std::cout << tag->GetID() << ". ";
            TerminalStyle::SetBackgroundColor(tag->GetColor());
            std::cout << "  ";
            TerminalStyle::ResetStyle();
            std::cout << " " << tag->GetLabel() << "\n";
        }
        break;

    case 2: {
        std::string label;
        std::cout << "Label: ";
        std::getline(std::cin, label);

        std::string color_str;
        std::cout << "Color (R, G, B): ";
        std::getline(std::cin, color_str);

        std::istringstream ss(color_str);
        int r, g, b;
        if(!(ss >> r >> g >> b))
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "Invalid color";
            TerminalStyle::ResetStyle();
            std::cout << "\n";
            break;
        }

        try
        {
            m_Context.tag_service->CreateTag(label, Color(r, g, b));
        }
        catch(const std::exception& e)
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << e.what();
            TerminalStyle::ResetStyle();
            std::cout << "\n";
        }
        break;
    }

    case 3: {
        std::string id_str;
        std::cout << "Tag ID: ";
        std::getline(std::cin, id_str);
        std::istringstream ss(id_str);
        int id;
        if(!(ss >> id))
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << "ID should be an integer";
            TerminalStyle::ResetStyle();
            std::cout << "\n";
            break;
        }

        try
        {
            m_Context.tag_service->DeleteTag(id);
        }
        catch(const std::exception& e)
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << e.what();
            TerminalStyle::ResetStyle();
            std::cout << "\n";
        }
        break;
    }
    
    default:
        std::cout << "\n";
        return std::make_unique<MainView>(m_Context);
        break;
    }

    std::cout << "\n";
    return std::make_unique<TagsView>(m_Context);
}