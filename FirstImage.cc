#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "color.h"
#include "vec3.h"

using std::cout;

int main()
{
    // Image
    int imageWidth = 256;
    int imageHeight = 256;

    // Rendering
    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines still remaining: " << (imageHeight - j) << ' ' << std::flush;

        for (int i = 0; i < imageWidth; i++)
        {
            auto pixelColor = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            writeColor(cout, pixelColor);
        }
    }

    std::clog << "\rDone.\n";

    return 0;
}

#endif