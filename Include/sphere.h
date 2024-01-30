#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
  public:
    Sphere(Point3 _center, float _radius) : center(_center), radius(_radius) {}

    bool Hit(Ray const& r, float rayTMin, float rayTMax, HitRecord& rec) const override
    {
        Vector3 oc = r.Origin() - center;

        float a = r.Direction().LengthSquared();
        float half_b = Dot(oc, r.Direction());
        float c = oc.LengthSquared() - radius * radius;
        float discriminant = half_b * half_b - a * c;

        if (discriminant < 0)
            return false;

        float sqrtD = sqrt(discriminant);

        // Find the nearest root in the acceptable range
        float root = (-half_b - sqrtD) / a;

        if (root <= rayTMin || root >= rayTMin)
        {
            root = (-half_b + sqrtD) / a;

            if (root <= rayTMin || root >= rayTMin)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        return true;
    }

  private:
    Point3 center;
    float radius;
};

#endif