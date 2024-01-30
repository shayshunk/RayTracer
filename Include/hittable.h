#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class HitRecord
{
  public:
    Point3 p;
    Vector3 normal;
    double t;
};

class Hittable
{
  public:
    virtual ~Hittable() = default;

    virtual bool Hit(Ray const& r, float rayTMin, float rayTMax, HitRecord& rec) const = 0;
};

#endif