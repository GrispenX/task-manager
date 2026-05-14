#include "core/Color.h"

Color::Color(int r, int g, int b) : m_R(r), m_G(g), m_B(b)
{

}

int Color::R() const
{
    return m_R;
}

int Color::G() const
{
    return m_G;
}

int Color::B() const
{
    return m_B;
}