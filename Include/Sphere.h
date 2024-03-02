#ifndef SPHERE_H
#define SPHERE_H

#include "RTWeekend.h"

class Sphere : public Hittable
{
  public:
    // Stationary sphere
    Sphere(Point3 _center, double _radius, shared_ptr<Material> _material)
        : center1(_center), radius(_radius), mat(_material), isMoving(false)
    {
        Vector3 radiusVec(radius, radius, radius);
        bBox = AABB(center1 - radiusVec, center1 + radiusVec);
    }

    // Moving sphere
    Sphere(Point3 _center1, Point3 _center2, double _radius, shared_ptr<Material> _material)
        : center1(_center1), radius(_radius), mat(_material), isMoving(true)
    {
        Vector3 radiusVec(radius, radius, radius);
        AABB box1(_center1 - radiusVec, _center1 + radiusVec);
        AABB box2(_center2 - radiusVec, _center2 + radiusVec);
        bBox = AABB(box1, box2);

        centerVector = _center2 - _center1;
    }

    bool Hit(Ray const& r, Interval rayT, HitRecord& rec) const override
    {
        Point3 center = isMoving ? Center(r.Time()) : center1;
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

    AABB BoundingBox() const override { return bBox; }

  private:
    Point3 center1;
    double radius;
    shared_ptr<Material> mat;
    bool isMoving;
    Vector3 centerVector;
    AABB bBox;

    Point3 Center(double time) const
    {
        // Lerping from center1 to center2 with time
        // t0 is at center1
        return center1 + time * centerVector;
    }
};

#endif