#include "core/Tag.h"

Tag::Tag(int id, std::string label, Color color) :
    m_ID(id),
    m_Label(label),
    m_Color(color)
{

}

int Tag::GetID() const
{
    return m_ID;
}

std::string Tag::GetLabel() const
{
    return m_Label;
}

Color Tag::GetColor() const
{
    return m_Color;
}

void Tag::SetID(int id)
{
    m_ID = id;
}

void Tag::SetLabel(std::string label)
{
    m_Label = label;
}

void Tag::SetColor(Color color)
{
    m_Color = color;
}