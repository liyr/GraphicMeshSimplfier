#include "Matrix.h"



Matrix::Matrix()
{
}


Matrix::~Matrix()
{
}

Matrix Matrix::operator+(const Matrix& p)
{
    Matrix res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res.ele_[i][j] = (*this).ele_[i][j] + p.ele_[i][j];
    return res;
}

Matrix Matrix::operator-(const Matrix& p)
{
    Matrix res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res.ele_[i][j] = (*this).ele_[i][j] + p.ele_[i][j];
    return res;
}

Matrix Matrix::operator-()
{
    Matrix res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res.ele_[i][j] = -(*this).ele_[i][j];
    return res;
}

Matrix Matrix::operator*(const Matrix& p)
{
}

void Matrix::mult(const SimpleOBJ::Vec3f& p, const double d, SimpleOBJ::Vec3f & res, double &resd)
{

}