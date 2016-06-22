#pragma once


class Vec4f;

class Matrix
{
    double ele_[4][4];
public:
    Matrix();
    ~Matrix();
    Matrix operator+(const Matrix &p) const;
    void operator+=(const Matrix& p);
    void operator-=(const Matrix& p);
    Matrix operator-(const Matrix &p) const;
    Matrix operator-();
    Matrix operator*(const Matrix& p) const;
    Vec4f operator*(const Vec4f& p) const;
    friend Matrix mult(const Vec4f& p1, const Vec4f& p2);
    double det3(int a = 3);
};

