
#include "Sirius/Renderer/Color.hpp"

namespace Sirius
{
    Color::Color(float r, float g, float b, float a): r(r), g(g),
        b(b), a(a)
    {}

    Color::Color(const Vec4& color): r(color.x), g(color.y),
        b(color.z), a(color.w)
    {}

    Color& Color::operator+=(const Color& color)
    {
        r += color.r;
        g += color.g;
        b += color.b;
        a += color.a;

        return *this;
    }

    Color& Color::operator-=(const Color& color)
    {
        r -= color.r;
        g -= color.g;
        b -= color.b;
        a -= color.a;

        return *this;
    }

    Color& Color::operator*=(const Color& color)
    {
        r *= color.r;
        g *= color.g;
        b *= color.b;
        a *= color.a;

        return *this;
    }

    Color::operator Vec4() const
    {
        return Vec4(r, g, b, a);
    }

    Color operator+(const Color& c1, const Color& c2)
    {
        return { c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a };
    }

    Color operator-(const Color& c1, const Color& c2)
    {
        return { c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a };
    }

    Color operator*(const Color& c1, const Color& c2)
    {
        return { c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a };
    }
}