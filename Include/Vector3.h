#ifndef Vector3_H
#define Vector3_H

#include <array>
#include <cmath>
#include <iostream>

#include "Timer.h"
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

    double LengthSquared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    double Length() const { return sqrt(LengthSquared()); }

    bool NearZero() const
    {
        // Return true if the vector is close to zero in all dimension
        double s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    static Vector3 Random() { return Vector3(RandomDouble(), RandomDouble(), RandomDouble()); }

    static Vector3 Random(double min, double max)
    {
        return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    static Vector3 Random(double minTheta, double maxTheta, double minPhi, double maxPhi)
    {
        return Vector3(1, RandomDouble(minTheta, maxTheta), RandomDouble(minPhi, maxPhi));
    }
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

inline double Dot(Vector3 const& u, Vector3 const& v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vector3 Cross(Vector3 const& u, Vector3 const& v)
{
    return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                   u.e[2] * v.e[0] - u.e[0] * v.e[2],
                   u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector3 UnitVector(Vector3 v)
{
    return v / v.Length();
}

/* inline Vector3 RandomInUnitSphere()
{
    while (true)
    {
        Vector3 p = Vector3::Random(-1, 1);

        if (p.LengthSquared() < 1)
            return p;
    }
} */

inline Vector3 RandomInUnitDisk()
{
    while (true)
    {
        Vector3 p(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);

        if (p.LengthSquared() < 1)
            return p;
    }
}

/* inline Vector3 RandomUnitVector()
{
    return UnitVector(RandomInUnitSphere());
} */
// Rejection method

inline Vector3 RandomUnitVector()
{
    Vector3 p = Vector3::Random(0, 1, 0, 2);
    p.e[0] = sin(p.e[1] * pi) * cos(p.e[2] * pi);
    p.e[1] = sin(p.e[1] * pi) * sin(p.e[2] * pi);
    p.e[2] = cos(p.e[1] * pi);

    return p;
}

inline Vector3 RandomOnHemisphere(Vector3 const& normal)
{
    Vector3 onUnitSphere = RandomUnitVector();

    if (Dot(onUnitSphere, normal) > 0.0)
        return onUnitSphere;
    else
        return -onUnitSphere;
}

inline Vector3 Reflect(Vector3 const& v, Vector3 const& n)
{
    return v - 2 * Dot(v, n) * n;
}

inline Vector3 Refract(Vector3 const& uv, Vector3 const& n, double eta_iOverEta_t)
{
    double cosTheta = fmin(Dot(-uv, n), 1.0);

    Vector3 rOutPerpendicular = eta_iOverEta_t * (uv + cosTheta * n);
    Vector3 rOutParralel = -sqrt(fabs(1.0 - rOutPerpendicular.LengthSquared())) * n;

    return rOutParralel + rOutPerpendicular;
}

#endif