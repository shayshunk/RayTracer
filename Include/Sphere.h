#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3.h"
#include "hittable.h"

class Sphere : public Hittable
{
  public:
    Sphere(Point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool Hit(Ray const& r, double rayTMin, double rayTMax, HitRecord& rec) const override
    {
        Vector3 oc = r.Origin() - center;
        auto a = r.Direction().LengthSquared();
        auto half_b = Dot(oc, r.Direction());
        auto c = oc.LengthSquared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root <= rayTMin || rayTMax <= root)
        {
            root = (-half_b + sqrtd) / a;
            if (root <= rayTMin || rayTMax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);

        Vector3 outwardNormal = (rec.p - center) / radius;
        rec.SetFaceNormal(r, outwardNormal);

        return true;
    }

  private:
    Point3 center;
    double radius;
};

#endif