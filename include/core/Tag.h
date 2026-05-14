#ifndef INCLUDE_CORE_TAG_H_
#define INCLUDE_CORE_TAG_H_

#include "core/Color.h"
#include <string>

class Tag
{
public:
    Tag(int id, std::string label, Color color);

    int GetID() const;
    std::string GetLabel() const;
    Color GetColor() const;

    void SetID(int id);
    void SetLabel(std::string label);
    void SetColor(Color color);

private:
    int m_ID;
    std::string m_Label;
    Color m_Color;
};

#endif // INCLUDE_CORE_TAG_H_