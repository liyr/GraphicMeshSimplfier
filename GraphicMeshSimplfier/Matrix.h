#pragma once


class Vec4f;

class Matrix
{
    double ele_[4][4];
public:
    Matrix();
    ~Matrix();
    Matrix operator+(const Matrix &p) const;
    Matrix operator-(const Matrix &p) const;
    Matrix operator-();
    Matrix operator*(const Matrix& p) const;
    Vec4f operator*(const Vec4f& p) const;
    friend Matrix mult(const Vec4f& p1, const Vec4f& p2);
};

