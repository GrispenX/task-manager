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
    do
    {
        std::cout << "Option: ";
        std::cin >> option;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (option < 1 || option > 4);

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
        std::cout << "\n";
        return std::make_unique<TagsView>(m_Context);
        break;

    case 2: {
        std::string label;
        std::cout << "Label: ";
        std::getline(std::cin, label);
        int r, g, b;
        std::cout << "Color (R, G, B): ";
        std::cin >> r >> g >> b;
        try
        {
            m_Context.tag_service->CreateTag(label, Color(r, g, b));
        }
        catch(const std::exception& e)
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << e.what() << "\n";
            TerminalStyle::ResetStyle();
        }
        
        std::cout << "\n";
        return std::make_unique<TagsView>(m_Context);
        break;
    }

    case 3: {
        int id;
        std::cout << "Tag ID: ";
        std::cin >> id;
        try
        {
            m_Context.tag_service->DeleteTag(id);
        }
        catch(const std::exception& e)
        {
            TerminalStyle::SetBackgroundColor(Red);
            TerminalStyle::SetBold();
            std::cout << e.what() << "\n";
            TerminalStyle::ResetStyle();
        }
        std::cout << "\n";
        return std::make_unique<TagsView>(m_Context);
        break;
    }
    
    default:
        std::cout << "\n";
        return std::make_unique<MainView>(m_Context);
        break;
    }
}