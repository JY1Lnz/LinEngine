#pragma once

#include <algorithm>

#include "Color.h"
#include "Triangle.h"
#include "Window.h"
#include "Model.h"
#include "Math.h"
#include "Camera.h"

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

    void DrawModel()
    {
        for (const auto& model : model_list_)
        {
            for (int i = 0; i < model.GetFaceSize(); ++i)
            {
                Triangle tr;
                for (int j = 0; j < 3; ++j)
                    tr[j] = model.GetVertex(i, j);
                DrawTriangle(tr);
            }
        }
    }

    bool AddModel(const std::string& model_name)
    {
        model_list_.emplace_back(model_name);
        return true;
    }

    void SetModelMatrix(float angle, float scale)
    {
        angle = angle * LIN_PI / 180.f;

        m4f rotation_m({
            {cos(angle), 0, sin(angle), 0},
            {0, 1, 0, 0},
            {-sin(angle), 0, cos(angle), 0},
            {0, 0, 0, 1}
            });

        m4f scale_m({
            {scale, 0, 0, 0},
            {0, scale, 0, 0},
            {0, 0, scale, 0},
            {0, 0, 0, 1}
            });

        m4f translate_m({
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
            });
        
        model = translate_m * rotation_m * scale_m;
    }

    void SetViewMatrix(const Camera* camera)
    {
        const vec3f& pos = camera->GetPos();
        m4f translate_m({
            {1, 0, 0, -pos.x},
            {0, 1, 0, -pos.y},
            {0, 0, 1, -pos.z},
            {0, 0, 0, 1}
            });
        m4f inv_m({
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, -1, 0},
            {0, 0, 0, 1}
            });
        view = inv_m * translate_m;
    }

    void SetProjectionMatrix(const Camera* camera)
    {
        // 先把视锥的远平面挤成和近平面相同的xy，再做一个正交投影
        float zNear = camera->GetZNear();
        float zFar = camera->GetZFar();
        float aspect = camera->GetAspect();
        float fov = camera->GetFov();
        m4f perspective_m({
            {zNear, 0, 0, 0},
            {0, zNear, 0, 0},
            {0, 0, zNear + zFar, -(zNear * zFar)},
            {0, 0, 1, 0}
            });
        float halve = fov / 2.0f * acos(-1) / 180.0f; // 一半fov的弧度
        float top = tan(halve) * zNear;
        float bottom = -top;
        float right = top * aspect;
        float left = -right;
        m4f orthographic_translate_m({
            {1, 0, 0, -(left + right) / 2},
            {0, 1, 0, -(bottom + top) / 2},
            {0, 0, 1, -(zNear + zFar) / 2},
            {0, 0, 0, 1}
            });
        m4f orthographic_translate_m({

            });
    }

private:
    m4f model;      // 模型矩阵
    m4f view;       // 视口矩阵
    m4f projection; // 投影矩阵

private:
    HDC screenHDC;
    std::vector<Model> model_list_;

private:
    int width_;
    int height_;
};