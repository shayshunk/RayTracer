#ifndef SPHERE_H
#define SPHERE_H

#include "RTWeekend.h"

class Sphere : public Hittable
{
  public:
    Sphere(Point3 _center, double _radius, shared_ptr<Material> _material)
        : center(_center), radius(_radius), mat(_material)
    {
    }

    bool Hit(Ray const& r, Interval rayT, HitRecord& rec) const override
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
        if (!rayT.Surrounds(root))
        {
            root = (-half_b + sqrtd) / a;
            if (!rayT.Surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);

        Vector3 outwardNormal = (rec.p - center) / radius;
        rec.SetFaceNormal(r, outwardNormal);
        rec.material = mat;

        return true;
    }

  private:
    Point3 center;
    double radius;
    shared_ptr<Material> mat;
};

#endif