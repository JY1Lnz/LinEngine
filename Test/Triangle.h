/*
 * @Descripttion: LinEngine
 * @version: 1.0.0
 * @Author: jy1lnz
 * @Date: 2022-09-12 22:37:35
 * @LastEditors: jy1lnz
 * @LastEditTime: 2022-09-12 22:43:50
 */

#pragma once

#include <functional>
#include <initializer_list>
#include <vector>

#include "Math.h"

class Triangle
{
public:
    Triangle(std::initializer_list<vec3f> list)
        :val_(list)
    {
    }
    Triangle(vec3f a, vec3f b, vec3f c)
        :val_({a, b, c})
    {
    }
    Triangle()
        :val_(3)
    {
    }

    vec3f GetPoint(int i) const
    {
        assert(i >= 0 && i < 3);
        return val_[i];
    }

    bool In(vec3f point) const
    {
        vec3f res = barycentric2D(val_[0], val_[1], val_[2], point);
        if (res.x < 0 || res.y < 0 || res.z < 0 || res.x + res.y + res.z > 1.f)
            return false;
        return true;
    }

    void ForEach(std::function<void(const vec3f& v)> func) const
    {
        for (int i = 0; i < 3; ++i)
            func(val_[i]);
    }

private:
    std::vector<vec3f> val_;
};