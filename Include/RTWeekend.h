#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
double const infinity = std::numeric_limits<double>::infinity();
double const pi = 3.1415926535897932385;

// Utilities
inline double DegreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

#include "ray.h"
#include "vec3.h"

#endif