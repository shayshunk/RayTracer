#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
  public:
    Ray() {}

    Ray(Point3 const& origin, Vector3 const& direction) : orig(origin), dir(direction) {}

    Point3 Origin() const { return orig; }

    Vector3 Direction() const { return dir; }

    Point3 at(double t) const
    {
        return orig + t * dir;
    }

  private:
    Point3 orig;
    Vector3 dir;
};

#endif