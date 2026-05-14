#ifndef INCLUDE_CONSOLE_TERMINALSTYLE_H_
#define INCLUDE_CONSOLE_TERMINALSTYLE_H_

#include "core/Color.h"

class TerminalStyle
{
public:
    static void Clear();
    static void ResetStyle();
    static void SetForegroundColor(Color color);
    static void SetBackgroundColor(Color color);
    static void SetBold();
    static void SetItalic();
    static void SetUnderline();
    static void SetStrikethrough();
};

#endif // INCLUDE_CONSOLE_TERMINALSTYLE_H_