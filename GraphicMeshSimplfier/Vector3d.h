#pragma once
#include <iostream>
#include <cmath>

class Vector3d
{
public:

    double x, y, z;
    explicit Vector3d(double x_ = 0, double y_ = 0, double z_ = 0) :x(x_), y(y_), z(z_)
    {}
    Vector3d operator+(const Vector3d &b) const
    {
        return Vector3d(x + b.x, y + b.y, z + b.z);
    }
    Vector3d operator-(const Vector3d &b) const
    {
        return Vector3d(x - b.x, y - b.y, z - b.z);
    }
    Vector3d operator*(const double b) const
    {
        return Vector3d(x * b, y * b, z * b);
    }
    Vector3d operator*(const Vector3d &b) const
    {
        return Vector3d(x * b.x, y * b.y, z * b.z);
    }
    double norm() const
    {
        return (1 / sqrt(x * x + y * y + z * z));
    }
    double distance(const Vector3d &b) const
    {
        return ((*this) - b).norm();
    }
    Vector3d& normalize()
    {
        return *this = *this * (1 / sqrt(x * x + y * y + z * z));
    }
    double dot(const Vector3d &b) const
    {
        return x * b.x + y * b.y + z * b.z;
    }
    Vector3d operator%(const Vector3d&b) const
    {
        return Vector3d(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    void calSphereRepre(Vector3d&normal, Vector3d&bi_normal, double &theta, double &phi) const
    {
        Vector3d tmp(this->dot(normal), this->dot(bi_normal), this->dot(normal%bi_normal));
        theta = acos(tmp.x);
        phi = atan2(tmp.z, tmp.y);
    }
    friend Vector3d calSphereVec(const Vector3d& normal, const Vector3d& bi_normal, const double &theta, const double &phi)
    {
        return (normal * cos(theta) + bi_normal * sin(theta) * cos(phi) + (bi_normal % normal) * sin(theta) * sin(phi));
    }
    friend std::ostream& operator<<(std::ostream& out, Vector3d& vec)
    {
        out << vec.x << " " << vec.y << " " << vec.z << std::endl;
        return out;
    }

    Vector3d rotate(const Vector3d &axis, const double angle) const
    {
        double temp;
        Vector3d cross;
        double cos_ang = cos(angle);
        double sin_ang = sin(angle);


        Vector3d out = (*this) * cos_ang;

        temp = dot(axis);
        temp = temp * (1.0 - cos_ang);
        out = out + axis * temp;

        cross = axis % (*this);
        out = out + cross * sin_ang;
        return out;
    }

};

