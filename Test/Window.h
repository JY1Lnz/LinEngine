#pragma once

#include <string>
#include <iostream>
#include <windows.h>

class Window;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* window = static_cast<Window*>(GetPropA(hWnd, "Owner"));
    if (!window)
        return DefWindowProcA(hWnd, msg, wParam, lParam);
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

class Window
{
public:
    Window(int w, int h, const std::string& name):
        width_(w),
        height_(h),
        name_(name)
    {
        WNDCLASS wndClass = { CS_BYTEALIGNCLIENT, 
                              (WNDPROC)MsgProc,
                              0, 0, 0, NULL, NULL, NULL, NULL,
                              TEXT("Test") };
        wndClass.hInstance = GetModuleHandle(NULL);
        if (!RegisterClass(&wndClass))
            return;
        window_ = CreateWindow(TEXT("Test"), TEXT("Test"),
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            0, 0, 0, 0, NULL, NULL,
            wndClass.hInstance, NULL);
        if (window_ == nullptr)
            return;
        hdc = GetDC(window_);
        screenHDC = CreateCompatibleDC(hdc);

        BITMAPINFO bitmapInfo = { { sizeof(BITMAPINFOHEADER), 
            width_, height_, 1, 32, BI_RGB, width_ * height_ * 4,
            0, 0, 0, 0} };
        LPVOID ptr;
        HBITMAP bitmapHandler = CreateDIBSection(
            screenHDC, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0
        );
        if (bitmapHandler == nullptr)
            return;
        HBITMAP screenObject = (HBITMAP)SelectObject(screenHDC, bitmapHandler);
        SetWindowPos(window_, NULL, 50, 50, width_, height_, 
            (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW) );
        ShowWindow(window_, SW_NORMAL);
        UpdateWindow(window_);
    }

    HDC     GetHDC() const { return hdc; }
    HDC     GetScreenHDC() const { return screenHDC; }
    void    CleanHDC()
    {

    }

    ~Window() = default;

private:
    HWND window_;
    HDC  hdc;
    HDC  screenHDC;

private:
    int width_;
    int height_;
    std::string name_;
};