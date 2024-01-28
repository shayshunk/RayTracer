#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

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
        for (int i = 0; i < imageWidth; i++)
        {
            float r = float(i) / (imageWidth - 1);
            float g = float(j) / (imageHeight - 1);
            float b = 0.0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            cout << i << ' ' << j << ' ' << 0 << '\n';
        }
    }

    return 0;
}

#endif