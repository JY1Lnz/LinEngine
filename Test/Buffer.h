#pragma once

#include <vector>

class Buffer
{
public:
    Buffer(int w, int h)
        : width_(w), height_(h)
    {}
    Buffer(int l)
        : width_(l), height_(l)
    {}
    Buffer()
    {}


private:
    int width_;
    int height_;
};

class DepthBuffer : public Buffer
{
public:
    DepthBuffer(int w, int h)
        : Buffer(w, h), buffer
    {
    }

private:
    std::vector<std::vector<float>> buffer;
};