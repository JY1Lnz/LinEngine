#pragma

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
        : model(), view(), projection(), viewport()
    {

    }

    virtual V2F VertexShader(const vec4f& v, const vec4f& color) = 0;
    virtual vec4f FragmentShader(const V2F& v2f) = 0;


public:
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
        m4f view_m({
            {camera->right.x, camera->right.y, camera->right.z, -(camera->right * camera->position_)},
            {camera->up.x, camera->up.y, camera->up.z, -(camera->up * camera->position_)},
            {-camera->front.x, camera->front.y, camera->front.z, camera->front * camera->position_},
            {0, 0, 0, 1}
            });

        view = view_m;
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
    }

protected:
    m4f model;      // 模型矩阵
    m4f view;       // 视口矩阵
    m4f projection; // 投影矩阵
    m4f viewport;   // 
};

class TestShader : public IShader
{
public:
    TestShader()
        : IShader()
    {

    }

    virtual V2F VertexShader(const vec4f& v, const vec4f& color) override
    {
        V2F v2f;
        v2f.world_pos = model * v;
        v2f.window_pos = projection * view * v2f.world_pos;
        v2f.color = color;
    }

    virtual vec4f FragmentShader(const V2F& v2f) override
    {

    }

};
