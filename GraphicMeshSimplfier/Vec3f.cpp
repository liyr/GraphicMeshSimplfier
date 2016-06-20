#include "Vec3f.h"
#include <math.h>
#include <cstring>

namespace SimpleOBJ
{

//////////////////////////////////////////////////////////////////////////
//  Constructors and Deconstructors
    Vec3f::Vec3f(void)
    {
        memset(_p,0,sizeof(float)*_len);
    }
    
    Vec3f::Vec3f(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3f::Vec3f(const Vec3f &v)
    {
        memcpy(_p,v._p,sizeof(float)*_len);
    }

    Vec3f::~Vec3f(void)
    {

    }

//////////////////////////////////////////////////////////////////////////
// Operators

    Vec3f& Vec3f::operator =( const Vec3f& v)
    {
        memcpy(_p,v._p,sizeof(float)*_len);        
        return (*this);
    }

    void Vec3f::operator +=(const Vec3f& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] += v._p[i];
    }
    void Vec3f::operator +=(float f)
    {
        for(int i=0;i<_len;i++)
            _p[i] += f;
    }

    void Vec3f::operator -=(const Vec3f& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= v._p[i];
    }
    void Vec3f::operator -=(float f)
    {
        for(int i=0;i<_len;i++)
            _p[i] -= f;
    }

    void Vec3f::operator *=(const Vec3f& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= v._p[i];
    }
    void Vec3f::operator *=(float f)
    {
        for(int i=0;i<_len;i++)
            _p[i] *= f;
    }

    void Vec3f::operator /=(const Vec3f& v)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= v._p[i];
    }
    void Vec3f::operator /=(float f)
    {
        for(int i=0;i<_len;i++)
            _p[i] /= f;
    }

    Vec3f Vec3f::operator +(const Vec3f&v) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + v[i];
        return res;
    }
    Vec3f Vec3f::operator +(float f) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] + f;
        return res;
    }

    Vec3f Vec3f::operator -(const Vec3f&v) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - v[i];
        return res;
    }
    Vec3f Vec3f::operator -(float f) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] - f;
        return res;
    }

    Vec3f Vec3f::operator *(const Vec3f&v) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * v[i];
        return res;
    }
    Vec3f Vec3f::operator *(float f) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] * f;
        return res;
    }

    Vec3f Vec3f::operator /(const Vec3f&v) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / v[i];
        return res;
    }
    Vec3f Vec3f::operator /(float f) const
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = (*this)[i] / f;
        return res;
    }

    Vec3f Vec3f::operator - () const 
    {
        Vec3f res;
        for(int i=0;i<_len;i++)
            res[i] = -(*this)[i];
        return res;
    }

    float Vec3f::operator | (const Vec3f&v) const
    {
        float res;
        for (int i = 0; i<_len; i++)
            res += (*this)[i] * v[i];
        return res;
    }

    Vec3f Vec3f::operator %(const Vec3f&v2) const
    {
        Vec3f res;
        res[0] = (*this)[1] * v2[2] - (*this)[2] * v2[1];
        res[1] = (*this)[2] * v2[0] - (*this)[0] * v2[2];
        res[2] = (*this)[0] * v2[1] - (*this)[1] * v2[0];
        return res;
    }

//////////////////////////////////////////////////////////////////////////
// Other Methods
    void Vec3f::Normalize()
    {
        float fSqr = L2Norm_Sqr();
        if(fSqr>1e-6)
            (*this) *= 1.0f/sqrt(fSqr);
    }

    float Vec3f::L2Norm_Sqr()
    {
        return _p[0]*_p[0] + _p[1]*_p[1] + _p[2]*_p[2];
    }
}

