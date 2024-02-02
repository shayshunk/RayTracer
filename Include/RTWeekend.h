#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
// double const infinity = std::numeric_limits<double>::infinity();
double const pi = 3.1415926535897932385;

// Utilities
inline double DegreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double RandomDouble()
{
    // Returns a random real number in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max)
{
    // Returns a random real number in [min, max)
    return min + (max - min) * RandomDouble();
}

// Common includes

#include "Interval.h"
#include "Ray.h"
#include "Vector3.h"

#endif