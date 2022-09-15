/*
 * @Descripttion: LinEngine
 * @version: 1.0.0
 * @Author: jy1lnz
 * @Date: 2022-09-12 20:17:31
 * @LastEditors: jy1lnz
 * @LastEditTime: 2022-09-12 22:44:33
 */
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Math.h"
#include "Model.h"

const int WindowWidth = 1024, WindowHeight = 1024;


// --------> x
// |
// |
// |
// v
// y

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
			//r->DrawTriangle(Triangle({ 0, 7, 0 }, { 470, 23, 0 }, { 318, 802, 0 }));
			r->DrawModel();
			BitBlt(w->GetHDC(), 0, 0, WindowWidth, WindowHeight, w->GetScreenHDC(), 0, 0, SRCCOPY);
		}
	}


}

void DoRender()
{
	Window* w = new Window(WindowWidth, WindowHeight, "JYL");
	Renderer* r = new Renderer(w->GetScreenHDC(), WindowWidth, WindowHeight);
	r->AddModel("african_head.obj");

	Run(w, r);
	
	delete w;
	delete r;
}

void Test()
{
}

int main()
{
	//Test();
	DoRender();

	return 0;
}