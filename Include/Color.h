#ifndef COLOR_H
#define COLOR_H

#include "Interval.h"
#include "Vector3.h"

using Color = Vector3;

inline double LinearToGamma(double linearComponent)
{
    return sqrt(linearComponent);
}

void WriteColor(std::ostream& out, Color pixelColor, int samplesPerPixel)
{
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    // Divide color by number of samples
    double scale = 1.0 / samplesPerPixel;

    r *= scale;
    g *= scale;
    b *= scale;

    // Apply gamma transform
    r = LinearToGamma(r);
    g = LinearToGamma(g);
    b = LinearToGamma(b);

    // Write the translated [0, 255] value of each primary color
    static Interval const intensity(0, 0.999);

    out << static_cast<int>(256 * intensity.Clamp(r)) << ", "
        << static_cast<int>(256 * intensity.Clamp(g)) << ", "
        << static_cast<int>(256 * intensity.Clamp(b)) << '\n';
}

#endif