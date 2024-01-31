#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

double const infinity = std::numeric_limits<double>::infinity();

class Interval
{
  public:
    double min, max;

    Interval() : min(+infinity), max(-infinity) {}

    Interval(double _min, double _max) : min(_min), max(_max) {}

    bool Contains(double x) const { return min <= x && x <= max; }

    bool Surrounds(double x) const { return min < x && x < max; }

    static Interval const empty, universe;
};

static Interval const empty(+infinity, -infinity);
static Interval const universe(-infinity, infinity);

#endif
