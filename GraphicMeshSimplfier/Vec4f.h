#pragma once
#include "Vec3f.h"

class Vec4f
    :public SimpleOBJ::Vec3f
{
public:
    float w = 1;
    Vec4f(float x, float y, float z, float w = 1): Vec3f(x, y, z), w(w)
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

    ~Vec4f()
    {
    }
};

