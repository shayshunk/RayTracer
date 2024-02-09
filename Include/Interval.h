#ifndef INTERVAL_H
#define INTERVAL_H

class Interval
{
  public:
    double min, max;

    Interval() : min(+infinity), max(-infinity) {}

    Interval(double _min, double _max) : min(_min), max(_max) {}

    bool Contains(double x) const { return min <= x && x <= max; }

    bool Surrounds(double x) const { return min < x && x < max; }

    double Clamp(double x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    double Size() const { return max - min; }

    Interval Expand(double delta) const
    {
        double padding = delta / 2;
        return Interval(min - padding, max + padding);
    }

    static Interval const empty, universe;
};

static Interval const empty(+infinity, -infinity);
static Interval const universe(-infinity, infinity);

#endif
