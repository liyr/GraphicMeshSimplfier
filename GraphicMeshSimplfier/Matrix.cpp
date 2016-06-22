#include "Matrix.h"
#include "Vec4f.h"
#include <cstring>


Matrix::Matrix()
{
}


Matrix::~Matrix()
{
}

Matrix Matrix::operator+(const Matrix& p) const
{
    Matrix res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res.ele_[i][j] = (*this).ele_[i][j] + p.ele_[i][j];
    return res;
}

void Matrix::operator+=(const Matrix& p)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ele_[i][j] += p.ele_[i][j];
}
void Matrix::operator-=(const Matrix& p)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ele_[i][j] -= p.ele_[i][j];
}

Matrix Matrix::operator-(const Matrix& p) const
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

Matrix Matrix::operator*(const Matrix& p) const
{
    Matrix res;
    memset(res.ele_, 0, sizeof(ele_));
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
                res.ele_[i][j] += (*this).ele_[i][k] * p.ele_[k][j];
    return res;
}

Vec4f Matrix::operator*(const Vec4f& p) const
{
    float aim[4] = { 0,0,0,0 };
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            aim[i] += ele_[i][j] * p[j];
        }
    Vec4f res(aim[0], aim[1], aim[2], aim[3]);
    return res;
}

double Matrix::det3(int a)
{
    switch (a)
    {
    case 3:
        return ele_[0][0] * ele_[1][1] * ele_[2][2] - ele_[0][0] * ele_[1][2] * ele_[2][1]
            - ele_[0][1] * ele_[1][0] * ele_[2][2] + ele_[0][1] * ele_[1][2] * ele_[2][0]
            + ele_[0][2] * ele_[1][0] * ele_[2][1] - ele_[0][2] * ele_[1][1] * ele_[2][0];
        break;
    case 0:
        return ele_[0][3] * ele_[1][1] * ele_[2][2] - ele_[0][3] * ele_[1][2] * ele_[2][1]
            - ele_[0][1] * ele_[1][3] * ele_[2][2] + ele_[0][1] * ele_[1][2] * ele_[2][3]
            + ele_[0][2] * ele_[1][3] * ele_[2][1] - ele_[0][2] * ele_[1][1] * ele_[2][3];
        break;
    case 1:
        return ele_[0][0] * ele_[1][3] * ele_[2][2] - ele_[0][0] * ele_[1][2] * ele_[2][3]
            - ele_[0][3] * ele_[1][0] * ele_[2][2] + ele_[0][3] * ele_[1][2] * ele_[2][0]
            + ele_[0][2] * ele_[1][0] * ele_[2][3] - ele_[0][2] * ele_[1][3] * ele_[2][0];
        break;
    case 2:
        return ele_[0][0] * ele_[1][1] * ele_[2][3] - ele_[0][0] * ele_[1][3] * ele_[2][1]
            - ele_[0][1] * ele_[1][0] * ele_[2][3] + ele_[0][1] * ele_[1][3] * ele_[2][0]
            + ele_[0][3] * ele_[1][0] * ele_[2][1] - ele_[0][3] * ele_[1][1] * ele_[2][0];
        break;
    }
    return 0;
}
