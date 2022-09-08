#include <iostream>
#include "Window.h"
#include "Renderer.h"

const int WindowWidth = 1024, WindowHeight = 1024;

void Run(Window* w, Renderer* r)
{
	MSG msg = {0};
	while( msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		}
	}

}

void DoRender(Window* w)
{

}

int main()
{
	Window* w = new Window(WindowWidth, WindowHeight, "JYL");
	Renderer* r = new Renderer(w->GetScreenHDC(), WindowWidth, WindowHeight);
	Run(w, r);

	return 0;
}