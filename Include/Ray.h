#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
  public:
    Ray() {}

    Ray(Point3 const& origin, Vector3 const& direction) : orig(origin), dir(direction), tm(0) {}

    Ray(Point3 const& origin, Vector3 const& direction, double time = 0)
        : orig(origin), dir(direction), tm(time)
    {
    }

    Point3 Origin() const { return orig; }

    Vector3 Direction() const { return dir; }

    double Time() const { return tm; }

    Point3 at(double t) const { return orig + t * dir; }

  private:
    Point3 orig;
    Vector3 dir;
    double tm;
};

#endif