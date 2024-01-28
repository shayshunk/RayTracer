#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
  public:
    Ray() {}

    Ray(point3 const& origin, Vector3 const& direction) : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }

    Vector3 direction() const { return dir; }

    point3 at(double t) const
    {
        return orig + t * dir;
    }

  private:
    point3 orig;
    Vector3 dir;
};

#endif