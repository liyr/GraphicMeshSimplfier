#pragma once
namespace SimpleOBJ{
    class Vec3f;
}

class Matrix
{
    double ele_[4][4];
public:
    Matrix();
    ~Matrix();
    Matrix operator+(const Matrix &p);
    Matrix operator-(const Matrix &p);
    Matrix operator-();
    Matrix operator*(const Matrix& p);
    void mult(const SimpleOBJ::Vec3f & p, const double d, SimpleOBJ::Vec3f & res, double &resd);
};

