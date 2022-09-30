#pragma

#include <iostream>

#include "Math.h"
#include "Camera.h"

struct V2F
{
    vec4f world_pos;
    vec4f window_pos;
    vec4f color;
    vec2f texvcoord;
    vec3f normal;
};

class IShader
{
public:
    IShader()
        : model(), view(), projection()
    {

    }

    virtual V2F VertexShader(const vec4f& v, const vec4f& color) const = 0;
    virtual vec4f FragmentShader(const V2F& v2f) const = 0;


public:
    void SetModelMatrix(float angle, float scale)
    {
        angle = angle * LIN_PI / 180.f;

        m4f rotation_x_m({
            {1, 0, 0, 0},
            {0, cos(angle), sin(angle), 0},
            {0, -sin(angle), cos(angle), 0},
            {0, 0, 0, 1}
            });

        m4f rotation_y_m({
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

        model = translate_m * rotation_y_m * rotation_x_m * scale_m;
        //std::cout << "model :" << std::endl;
        //std::cout << model << std::endl;
        //std::cout << rotation_m << std::endl;
    }

    void SetViewMatrix(const Camera* camera)
    {
        m4f view_m({
            {camera->right.x, camera->right.y, camera->right.z, -(camera->right * camera->position_)},
            {camera->up.x, camera->up.y, camera->up.z, -(camera->up * camera->position_)},
            {-camera->front.x, camera->front.y, camera->front.z, camera->front * camera->position_},
            {0, 0, 0, 1}
            });

        view = view_m;
        //std::cout << "ViewMatrix :" << std::endl;
        //std::cout << view << std::endl;
    }

    void SetProjectionMatrix(const Camera* camera)
    {
        float zNear = camera->GetZNear();
        float zFar = camera->GetZFar();
        float aspect = camera->GetAspect();
        float fov = camera->GetFov();
        m4f perspective_m({
            {zNear, 0, 0, 0},
            {0, zNear, 0, 0},
            {0, 0, zNear + zFar, -(zNear * zFar)},
            {0, 0, -1, 0}
            });
        float halve = fov / 2.0f * acos(-1) / 180.0f;
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
        m4f orthographic_scale_m({
            {2.0f / (right - left), 0, 0, 0},
            {0, 2.0f / (top - bottom), 0, 0},
            {0, 0, 2.0f / (zNear - zFar), 0},
            {0, 0, 0, 1}
            });

        projection = orthographic_scale_m * orthographic_translate_m * perspective_m;
        //std::cout << "projection :" << std::endl;
        //std::cout << projection << std::endl;
    }

protected:
    m4f model;      // 模型矩阵
    m4f view;       // 视口矩阵
    m4f projection; // 投影矩阵
};

class TestShader : public IShader
{
public:
    TestShader()
        : IShader()
    {

    }

    virtual V2F VertexShader(const vec4f& v, const vec4f& color) const override
    {
        V2F v2f;
#ifdef _DEBUG
        std::cout << "VertexShader" << std::endl;
        std::cout << "  P : " << v << std::endl;
        v2f.world_pos = model * v;
        std::cout << "  P -> model transform: " << v2f.world_pos << std::endl;
        v2f.world_pos = view * model * v;
        std::cout << "  P -> model, view transform: " << v2f.world_pos << std::endl;
        v2f.world_pos = projection * view * model * v;
        std::cout << "  P -> model, view, projection transform: " << v2f.world_pos << std::endl;


#else
        v2f.world_pos = model * v;
        v2f.window_pos = projection * view * v2f.world_pos;

#endif // DEBUG
        v2f.color = color;

        return v2f;
    }

    virtual vec4f FragmentShader(const V2F& v2f) const override
    {
        return v2f.color;
    }

};
