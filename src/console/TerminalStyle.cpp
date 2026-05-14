#include "console/TerminalStyle.h"
#include <iostream>
#include <format>

void TerminalStyle::Clear()
{
    std::cout << "\033[2J";
}

void TerminalStyle::ResetStyle()
{
    std::cout << "\033[0m";
}

void TerminalStyle::SetForegroundColor(Color color)
{
    std::cout << std::format("\033[38;2;{};{};{}m", color.R(), color.B(), color.B());
}

void TerminalStyle::SetBackgroundColor(Color color)
{
    std::cout << std::format("\033[48;2;{};{};{}m", color.R(), color.G(), color.B());
}

void TerminalStyle::SetBold()
{
    std::cout << "\033[1m";
}

void TerminalStyle::SetItalic()
{
    std::cout << "\033[3m";
}

void TerminalStyle::SetUnderline()
{
    std::cout << "\033[4m";
}

void TerminalStyle::SetStrikethrough()
{
    std::cout << "\033[9m";
}