#include "core/Color.h"
#include <stdexcept>

Color::Color(int r, int g, int b) : m_R(r), m_G(g), m_B(b)
{
    if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) throw std::runtime_error("R G B color parts should be in range [0; 255]");
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