// 数学库
#include <vector>
#include <assert.h>

template<typename T, size_t L>
struct Vector
{
public:
    Vector(std::initializer_list<T> val)
    {
        for (int i = 0;i < L; ++i)
            val[i] = *(val.begin()+i);
    }
    Vector(const Vector<T, L>& rhs)
    {
        for (int i = 0;i < L; ++i)
            val[i] = rhs.val[i];
    }
    Vector()
    {
        for (int i = 0;i < L; ++i)
            val[i] = T();
    }
    T&       operator [](const size_t i) 
    {
        assert(i < L && i >= 0);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < L && i >= 0);
        return val[i];
    }

private:
    T val[L];
};

template<typename T>
struct Vector<T, 2>
{
    union 
    {
        struct { T x, y;   };
        struct { T u, v;   };
        struct { T val[2]; };
    };
    T& operator[] (int i)
    {
        assert(i >= 0 && i < 2);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < 2 && i >= 0);
        return val[i];
    }
};

template<typename T>
struct Vector<T, 3>
{
    union
    {
        struct { T x, y, z;   };
        struct { T val[3];    };
    };
    T& operator[] (int i)
    {
        assert(i >= 0 && i < 3);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < 3 && i >= 0);
        return val[i];
    }
};

template<typename T>
struct Vector<T, 4>
{
    union 
    {
        struct { T x, y, z, w; };
        struct { T val[4];     };
    };
    T& operator[] (int i)
    {
        assert(i >= 0 && i < 4);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < 4 && i >= 0);
        return val[i];
    }
};


template<typename T, size_t row, size_t col>
class Matrix
{
private:
    Vector<T, col> val[row]; // 每行存的是列向量
public:
    static Matrix<T, row, col> Idtentity()
    {
        Matrix<T, row, col> res;
        for (int i = 0;i < row; ++i) res[i][i] = 1;
        return res;
    }
    Matrix(const Matrix<T, row, col>& rhs)
    {
        for (int i = 0;i < row; ++i)
            val[i] = rhs.val[i];
    }
    Matrix()
    {
        for (int i = 0;i < row; ++i)
            val[i] = Vector<T, col>();
    }
    Vector<T, col>&       operator[] (int i)
    {
        assert(i >= 0 && i < row);
        return val[i];
    }
    const Vector<T, col>& operator[] (int i) const
    {
        assert(i >= 0 && i < row);
        return val[i];
    }
};

template<typename T, size_t R1, size_t C1, size_t C2>
Matrix<T, R1, C2> operator*(const Matrix<T, R1, C1>& lhs, const Matrix<T, C1, C2>& rhs)
{
    Matrix<T, R1, C2> res;
    for (int i = 0;i < R1; ++i)
    {
        for (int j = 0;j < C2; ++j)
        {
            res[i][j] = 0;
            for (int k = 0;k < C1; ++k)
            {
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}

