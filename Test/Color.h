#pragma once

#include "Util.h"

struct Color
{
    float r, g, b, a;
    Color (float cr, float cg, float cb, float ca = 0)
        : r(cr), g(cg), b(cb), a(ca)
    {}
    Color (float v)
        : r(v), g(v), b(v), a(v)
    {}
    Color ()
    {}
    ~Color() = default;

    Color operator + (const Color& right) const
    {
        Color returnValue(r + right.r, g + right.g, b + right.b, a + right.a);
        return returnValue;
    }
    Color operator - (const Color& right) const
    {
        Color returnValue(r - right.r, g - right.g, b - right.b, a - right.a);
        return returnValue;
    }
    Color operator * (const Color& right) const
    {
        Color returnValue(r * right.r, g * right.g, b * right.b, a * right.a);
        return returnValue;
    }

    Color operator * (float value) const
    {
        Color returnValue(r * value, g * value, b * value, a * value);
        return returnValue;
    }

    Color operator / (float value) const
    {
        float rhvalue = 1.0f / value;
        Color returnValue(r * rhvalue, g * rhvalue, b * rhvalue, a * rhvalue);
        return returnValue;
    }

    Color Lerp(const Color& left, const Color& right, float t)
    {
        return left + (right - left) * t;
    }
};