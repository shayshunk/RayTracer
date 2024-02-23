#ifndef HITTABLE_H
#define HITTABLE_H

#include "AABB.h"
#include "Ray.h"

class Material;

class HitRecord
{
  public:
    Point3 p;
    Vector3 normal;
    shared_ptr<Material> material;
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

    virtual AABB BoundingBox() const = 0;
};

#endif