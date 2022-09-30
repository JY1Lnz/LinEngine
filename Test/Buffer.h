#pragma once

#include <vector>

class Buffer
{
public:
    Buffer(int w, int h)
        : width_(w), height_(h)
    {}
    Buffer()
    {}


protected:
    int width_;
    int height_;
};

class DepthBuffer : public Buffer
{
public:
    DepthBuffer(int w, int h)
        : Buffer(w, h), buffer_(w, std::vector<float>(h))
    {
    }
    void CleanMin()
    {
        for (int i = 0; i < width_; ++i)
        {
            for (int j = 0; j < height_; ++j)
                buffer_[i][j] = -1000000000;
        }
    }
    void CleanMax()
    {
        for (int i = 0; i < width_; ++i)
        {
            for (int j = 0; j < height_; ++j)
                buffer_[i][j] = 1000000000;
        }
    }
    void Set(int x, int y, float dep)
    {
        buffer_[x][y] = dep;
    }

    float Get(int x, int y) const
    {
        return buffer_[x][y];
    }

private:
    std::vector<std::vector<float>> buffer_;
};