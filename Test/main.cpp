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
#include "Mesh.h"
#include "perf.h"
#include "Input.h"

const int WindowWidth = 1024, WindowHeight = 1024;
#define POS_OFFSET 0.1f


// --------> x
// |
// |
// |
// v
// y

Mesh m;

Mesh CreatePlane(const vec3f& leftTop, const vec3f& leftBottom, const vec3f& rightBottom, const vec3f& rightTop, const vec3f& normal, bool set = false) {
	Mesh result(4, 6);
	result.VBO[0] = vec324(leftTop, 1.0f);
	result.color[0] = set ? vec4f(255, 0, 0, 255) : vec4f(255, 0, 0, 255);
	result.VBO[1] = vec324(rightTop, 1.0f);
	result.color[1] = set ? vec4f(255, 0, 0, 255) : vec4f(0, 255, 0, 255);
	result.VBO[2] = vec324(rightBottom, 1.0f);
	result.color[2] = set ? vec4f(255, 0, 0, 255) : vec4f(0, 0, 255, 0);
	result.VBO[3] = vec324(leftBottom, 1.0f);
	result.color[3] = set ? vec4f(255, 0, 0, 255) : vec4f(255, 0, 255, 255);
	//绘制三角形的顺序是 左上->右下->右下 左上->左下->右上 都是逆时针方向 
	result.EBO[0] = 0;
	result.EBO[1] = 2;
	result.EBO[2] = 1;
	result.EBO[3] = 0;
	result.EBO[4] = 3;
	result.EBO[5] = 2;
	return result;
}

Mesh CreateBox(const vec3f& center, float radius) {
	Mesh result;
	Mesh front = CreatePlane(
		center + vec3f(-radius, radius, -radius),
		center + vec3f(-radius, -radius, -radius),
		center + vec3f(radius, -radius, -radius),
		center + vec3f(radius, radius, -radius),
		vec3f(0, 0, 1), true
	);
	result.AddMesh(front);

	Mesh left = CreatePlane(
		center + vec3f(-radius, radius, radius),
		center + vec3f(-radius, -radius, radius),
		center + vec3f(-radius, -radius, -radius),
		center + vec3f(-radius, radius, -radius),
		vec3f(-1, 0, 0)
	);
	result.AddMesh(left);

	Mesh right = CreatePlane(
		center + vec3f(radius, radius, -radius),
		center + vec3f(radius, -radius, -radius),
		center + vec3f(radius, -radius, radius),
		center + vec3f(radius, radius, radius),
		vec3f(1, 0, 0)
	);
	result.AddMesh(right);

	Mesh back = CreatePlane(
		center + vec3f(radius, radius, radius),
		center + vec3f(radius, -radius, radius),
		center + vec3f(-radius, -radius, radius),
		center + vec3f(-radius, radius, radius),
		vec3f(0, 0, -1)
	);
	result.AddMesh(back);

	Mesh up = CreatePlane(
		center + vec3f(-radius, radius, radius),
		center + vec3f(-radius, radius, -radius),
		center + vec3f(radius, radius, -radius),
		center + vec3f(radius, radius, radius),
		vec3f(0, 1, 0)
	);
	result.AddMesh(up);

	Mesh down = CreatePlane(
		center + vec3f(-radius, -radius, -radius),
		center + vec3f(-radius, -radius, radius),
		center + vec3f(radius, -radius, radius),
		center + vec3f(radius, -radius, -radius),
		vec3f(0, -1, 0)
	);
	result.AddMesh(down);

	return result;
}

void SetMesh()
{
	m = CreateBox(vec3f(0, 0, 0), 1);
}

void UpdateController(Camera* camera, IShader* shader)
{
	if (IS_KEY_DOWN('W'))
	{
		camera->position_.z += POS_OFFSET;
		shader->SetViewMatrix(camera);
	}
	if (IS_KEY_DOWN('S'))
	{
		camera->position_.z -= POS_OFFSET;
		shader->SetViewMatrix(camera);
	}
	if (IS_KEY_DOWN('A'))
	{
		camera->position_.x -= POS_OFFSET;
		shader->SetViewMatrix(camera);
	}
	if (IS_KEY_DOWN('D'))
	{
		camera->position_.x += POS_OFFSET;
		shader->SetViewMatrix(camera);
	}
	if (IS_KEY_DOWN('E'))
	{
		camera->position_.y += POS_OFFSET;
		shader->SetViewMatrix(camera);
	}
	if (IS_KEY_DOWN('Q'))
	{
		camera->position_.y -= POS_OFFSET;
		shader->SetViewMatrix(camera);
	}
}

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
	Camera* camera = new Camera();
	IShader* shader = new TestShader();
	camera->fov_ = 60;
	camera->aspect_ = 1;
	camera->zNear_ = 20.f;
	camera->zFar_ = 100.f;
	camera->position_ = { 0, 0, 5 };
	camera->front = { 0, 0, -1 };
	camera->right = { 1, 0, 0 };
	camera->up = { 0, 1, 0 };
	shader->SetViewMatrix(camera);
	shader->SetProjectionMatrix(camera);
	shader->SetModelMatrix(0, 1.0);
	float angle = 0.f;
	float x_offset = 0, y_offset = 0, z_offset = 0;

	//Run(w, r);
	MSG msg = {0};
	SetMesh();
	int cnt = 0;
	while( msg.message != WM_QUIT)
	{

		UpdateController(camera, shader);

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			{
				//CalTime _("Clean");
				r->Clean();
			}
			angle = angle + 1.f;
			if (angle >= 360) angle -= 360;
			//shader->SetModelMatrix(angle, 1.0);
			{

				//CalTime _("DrawMesh");
				r->DrawMesh(m, *shader);
			}
			{
				//CalTime _("BitBlt");
				BitBlt(w->GetHDC(), 0, 0, WindowWidth, WindowHeight, w->GetScreenHDC(), 0, 0, SRCCOPY);
			}
		}
	}
	
	delete camera;
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