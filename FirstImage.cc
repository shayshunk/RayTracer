#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

using std::cout;

Color rayColor(Ray const& r)
{
    return Color(0, 0, 0);
}

int main()
{
    // Image
    float aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // Calculating image height and checking that it's >= 1
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1)? 1 : imageHeight;

    // Setting up Camera
    float focalLength = 1.0;
    float viewportHeight = 2.0;

    float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);
    Point3 cameraCenter(0, 0, 0);

    // Calculating vectors across the horizontal and down the vertical viewport edges
    Vector3 viewportU(viewportWidth, 0, 0);
    Vector3 viewportV(0, -viewportHeight, 0);

    // Calculating horizontal and vertical delta vectors from pixel to pixel
    Vector3 pixelDeltaU = viewportU / imageWidth;
    Vector3 pixelDeltaV = viewportV / imageHeight;

    // Calculating the location of the upper left pixel
    Point3 viewportUpperLeft = cameraCenter - Vector3(0, 0, focalLength) - (viewportU / 2) - (viewportV / 2);
    Point3 pixel00Location = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));

    // Rendering
    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++)
    {
        std::clog << "Scanlines remaining: " << (imageHeight - i) << '\r';
        cout.flush();

        for (int j = 0; j < imageWidth; j++)
        {
            Point3 pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
            Vector3 rayDirection = pixelCenter - cameraCenter;

            Ray r(cameraCenter, rayDirection);

            Color pixelColor = rayColor(r);
            writeColor(cout, pixelColor);
        }
    }

    std::clog << "Done.\n";

    return 0;
}

#endif