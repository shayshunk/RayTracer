#ifndef AABB_H
#define AABB_H

#include "Interval.h"
#include "RTWeekend.h"
#include "Ray.h"

class AABB
{
  public:
    Interval x, y, z;

    AABB() {}  // Default is empty since intervals are empty by default

    AABB(Interval const& ix, Interval const& iy, Interval const& iz) : x(ix), y(iy), z(iz) {}

    AABB(Point3 const& a, Point3 const& b)
    {
        // Treat points a and b as extrema for bounding box
        x = Interval(fmin(a[0], b[0]), fmax(a[0], b[0]));
        y = Interval(fmin(a[1], b[1]), fmax(a[1], b[1]));
        z = Interval(fmin(a[2], b[2]), fmax(a[2], b[2]));
    }

    AABB(AABB const& box0, AABB const& box1)
    {
        x = Interval(box0.x, box1.x);
        y = Interval(box0.y, box1.y);
        z = Interval(box0.z, box1.z);
    }

    Interval const& Axis(int n) const
    {
        if (n == 1)
            return y;
        if (n == 2)
            return z;
        return x;
    }

    bool Hit(Ray const& r, Interval rayT) const
    {
        for (int a = 0; a < 3; a++)
        {
            double invD = 1 / r.Direction()[a];
            double orig = r.Origin()[a];

            double t0 = (Axis(a).min - orig) * invD;
            double t1 = (Axis(a).max - orig) * invD;

            if (invD < 0)
                std::swap(t0, t1);

            if (t0 > rayT.min)
                rayT.min = t0;
            if (t1 < rayT.max)
                rayT.max = t1;

            if (rayT.max <= rayT.min)
                return false;
        }

        return true;
    }
};

#endif