#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class HitRecord
{
  public:
    Point3 p;
    Vector3 normal;
    double t;
    bool frontFace;

    void SetFaceNormal(Ray const& r, Vector3 const& outwardNormal)
    {
        // Sets the hit record normal vector
        // NOTE: the outward normal parameter is assumed to be a unit vector
        frontFace = Dot(r.Direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
  public:
    virtual ~Hittable() = default;

    virtual bool Hit(Ray const& r, Interval rayT, HitRecord& rec) const = 0;
};

#endif