#include <iostream>
#include "Math.h"

int main()
{
    vec3f a(1.4f, 2.9f, 3.6f), b(3.0f, 2.1f, 1.9f);
    vec3f x;
    a = a*b;
    std::cout << a.x << ' ' << a.y << ' ' << a.z << std::endl;

    return 0;
}