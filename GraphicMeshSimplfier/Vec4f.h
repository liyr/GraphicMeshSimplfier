#pragma once
#include "Vec3f.h"

class Vec4f
    :public SimpleOBJ::Vec3f
{
public:
    float w = 1;
    Vec4f(float x = 0, float y = 0, float z = 0, float w = 1): Vec3f(x, y, z), w(w)
    {
    }

    __forceinline float& operator [](int index) override
    {
        assert(index >= 0 && index < 4);
        if (index != 4)
            return _p[index];
        else
            return w;
    }
    __forceinline const float& operator [](int index) const override
    {
        assert(index >= 0 && index < 4);
        if (index != 4)
            return _p[index];
        else
            return w;
    }

    float operator | (const Vec4f&v) const
    {
        float res = 0;
        for (int i = 0; i < 4; i++)
            res += (*this)[i] * v[i];
        return res;
    }

    bool Vec4f::operator == (const Vec4f&v) const
    {
        return (_p[0] == v[0]) && (_p[1] == v[1]) && (_p[2] == v[2]) && (_p[3] == v[3]);
    }

    ~Vec4f()
    {
    }
};

