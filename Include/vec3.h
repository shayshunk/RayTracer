#ifndef Vector3_H
#define Vector3_H

#include <array>
#include <cmath>
#include <iostream>
using std::sqrt, std::array;

class Vector3
{
  public:
    array<double, 3> e;

    Vector3() : e{0, 0, 0} {}

    Vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[1]; }

    Vector3& operator+=(Vector3 const& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    Vector3& operator-=(Vector3 const& v) { return *this += -v; }

    Vector3& operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    Vector3& operator/=(double t) { return *this *= 1 / t; }

    double lengthSquared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    double length() const { return sqrt(lengthSquared()); }
};

// point3 is just an alias for Vector3, but useful for geometric clarity
using Point3 = Vector3;

// Vector Utilities

inline std::ostream& operator<<(std::ostream& out, Vector3 const& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(Vector3 const& u, Vector3 const& v)
{
    return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator-(Vector3 const& u, Vector3 const& v)
{
    return u + (-v);
}

inline Vector3 operator*(Vector3 const& u, Vector3 const& v)
{
    return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator*(double t, Vector3 const& v)
{
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(Vector3 const& v, double t)
{
    return t * v;
}

inline Vector3 operator/(Vector3 const& u, Vector3 const& v)
{
    return Vector3(u.e[0] / v.e[0], u.e[1] / v.e[1], u.e[2] / v.e[2]);
}

inline Vector3 operator/(Vector3 const& v, double t)
{
    return (1 / t) * v;
}

inline double dot(Vector3 const& u, Vector3 const& v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vector3 cross(Vector3 const& u, Vector3 const& v)
{
    return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] - v.e[0]);
}

inline Vector3 unitVector(Vector3 v)
{
    return v / v.length();
}

#endif