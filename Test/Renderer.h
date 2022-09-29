#pragma once

#include <algorithm>

#include "Color.h"
#include "Triangle.h"
#include "Window.h"
#include "Model.h"
#include "Math.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h" 
#include "perf.h"

class Renderer
{
public:
    Renderer(HDC hdc, int w, int h)
        :screenHDC(hdc),
        width_(w),
        height_(h)
    {

    }

    void PerspectiveDivision(V2F& v)
    {
        // Í¸ÊÓ³ý·¨
        v.window_pos = v.window_pos / v.window_pos.w;
        v.window_pos.w = 1.0f;
        v.window_pos.z = (v.window_pos.z + 1.0f) * 0.5f;
    }

    void SetViewPort()
    {
        m4f result({
            {width_ / 2.f, 0, 0, width_ / 2.f},
            {0, height_ / 2.f, 0, height_ / 2.f},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
            });
        view_port = result;
    }

    void DrawPixel(vec2i p, const Color& color)
    {
        SetPixel(screenHDC, p.x, p.y,
            RGB(color.r, color.g, color.b));
    }

    void DrawRect()
    {
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
        for (int x = min_p.x; x <= max_p.x; ++x)
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

    void DrawMeshTriangle(V2F v2f[3], const IShader& shader)
    {
        //CalTime _("Draw Tri");
        Triangle tri({vec423(v2f[0].window_pos), vec423(v2f[1].window_pos), vec423(v2f[2].window_pos)});
        vec3f min_p(tri.GetPoint(0)), max_p(tri.GetPoint(0));
        tri.ForEach([&](vec3f p) -> void {
            min_p.x = min(min_p.x, p.x);
            min_p.y = min(min_p.y, p.y);

            max_p.x = max(max_p.x, p.x);
            max_p.y = max(max_p.y, p.y);
            });
        for (int x = min_p.x; x <= max_p.x; ++x)
        {
            for (int y = min_p.y; y <= max_p.y; ++y)
            {
                vec3f bar = tri.GetBaryCentric2D({ (float)x, (float)y, (float)0 });
                if (bar.x < 0 || bar.y < 0 || bar.z < 0 || bar.x + bar.y + bar.z > 1.f)
                    continue;
                vec4f color = v2f[0].color * bar.x + v2f[1].color * bar.y + v2f[2].color * bar.z;
                DrawPixel({ x, y }, Color(color.x, color.y, color.z, color.w));
            }
        }
             
    }

    void DrawMesh(const Mesh& mesh, const IShader& shader)
    {
        if (mesh.EBO.empty())
        {
            return;
        }

        for (int i = 0; i < mesh.EBO.size(); i += 3)
        {
            //CalTime _("every EBO");
            SetViewPort();
            vec4f   p[3];
            vec4f   c[3];
            V2F     v2f[3];
            for (int j = 0; j < 3; ++j)
            {
                p[j] = mesh.VBO[mesh.EBO[i + j]];
                c[j] = mesh.color[mesh.EBO[i + j]];
            }
            //std::cout << "P0 : " << p[0] << " P1 : " << p[1] << " P2 : " << p[2] << std::endl;
            //std::cout << " MVP :" << std::endl;

            for (int j = 0; j < 3; ++j)
            {
                v2f[j] = shader.VertexShader(p[j], c[j]);
                PerspectiveDivision(v2f[j]);
                v2f[j].window_pos = view_port * v2f[j].window_pos;
                //std::cout << " P" << j << " : " << v2f[j].window_pos;
            }
            //std::cout << std::endl;
            DrawMeshTriangle(v2f, shader);
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

    void Clean()
    {
        BitBlt(screenHDC, 0, 0, width_, height_, NULL, NULL, NULL, BLACKNESS);
    }

private:
    HDC screenHDC;
    std::vector<Model> model_list_;
    m4f view_port;

private:
    int width_;
    int height_;
};