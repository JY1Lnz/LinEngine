#pragma once

#include "Window.h"
#include "Color.h"

class Renderer
{
public:
    Renderer(HDC hdc, int w, int h)
        :screenHDC(hdc),
        width_(w),
        height_(h)
    {

    }

    void DrawPixel(int x, int y, const Color& color)
    {
        SetPixel(screenHDC, x, y,
            RGB(255 * color.r, 255 * color.g, 255 * color.b));
    }

private:
    HDC screenHDC;

private:
    int width_;
    int height_;
};