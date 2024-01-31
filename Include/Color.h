#ifndef COLOR_H
#define COLOR_H

#include "Vector3.h"

using Color = Vector3;

void WriteColor(std::ostream& out, Color pixelColor)
{
    // Write the translated [0, 255] value of each primary color
    out << static_cast<int>(255.999 * pixelColor.x()) << ", "
        << static_cast<int>(255.999 * pixelColor.y()) << ", "
        << static_cast<int>(255.999 * pixelColor.z()) << '\n';
}

#endif