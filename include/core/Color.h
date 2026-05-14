#ifndef INCLUDE_CORE_COLOR_H_
#define INCLUDE_CORE_COLOR_H_

class Color
{
public:
    Color(int r, int g, int b);

    int R() const;
    int G() const;
    int B() const;

private:
    int m_R;
    int m_G;
    int m_B;
};

#define White Color(255, 255, 255)
#define Black Color(0, 0, 0)
#define Red Color(255, 0, 0)
#define Green Color(0, 255, 0)
#define Blue Color(0, 0, 255)
#define Yellow Color(255, 255, 0)
#define Purple Color(255, 0, 255)
#define Cyan Color(0, 255, 255)

#endif // INCLUDE_CORE_COLOR_H_