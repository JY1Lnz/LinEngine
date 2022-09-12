#pragma once

#include <algorithm>

#include "Color.h"
#include "Triangle.h"
#include "Window.h"

class Renderer
{
public:
    Renderer(HDC hdc, int w, int h)
        :screenHDC(hdc),
        width_(w),
        height_(h)
    {

    }

    void DrawPixel(vec2i p, const Color& color)
    {
        SetPixel(screenHDC, p.x, p.y,
            RGB(color.r, color.g, color.b));
    }

    void DrawTriangle(const Triangle& triangle)
    {
        vec3f min_p(triangle.GetPoint(0)), max_p(triangle.GetPoint(0));
        triangle.ForEach([&](vec3f p) -> void {
            min_p.x = min(min_p.x, p.x);
            min_p.y = min(min_p.y, p.y);

            max_p.x = max(max_p.x, p.x);
            max_p.y = max(max_p.y, p.y);
            });
        for (int x = min_p.x; x <= max_p.y; ++x)
        {
            for (int y = min_p.y; y <= max_p.y; ++y)
            {
                if (triangle.In({ (float)x, (float)y, (float)0 }))
                {
                    DrawPixel({ x, y }, Color(255, 0, 0));
                }
            }
        }
    }

private:
    HDC screenHDC;

private:
    int width_;
    int height_;
};