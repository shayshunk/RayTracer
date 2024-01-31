#include "RTWeekend.h"

#include <cmath>
#include <iostream>

#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

using std::cout;

Color RayColor(Ray const& r, Hittable const& world)
{
    HitRecord rec;
    if (world.Hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vector3 unitDirection = UnitVector(r.Direction());
    double a = 0.5 * (unitDirection.y()) + 1.0;
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // Calculating image height and checking that it's >= 1
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // World
    HittableList world;

    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -100.5, 1), 100));

    // Setting up Camera
    double focalLength = 1.0;
    double viewportHeight = 2.0;

    double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
    Point3 cameraCenter(0, 0, 0);

    // Calculating vectors across the horizontal and down the vertical viewport edges
    Vector3 viewportU(viewportWidth, 0, 0);
    Vector3 viewportV(0, -viewportHeight, 0);

    // Calculating horizontal and vertical delta vectors from pixel to pixel
    Vector3 pixelDeltaU = viewportU / imageWidth;
    Vector3 pixelDeltaV = viewportV / imageHeight;

    // Calculating the location of the upper left pixel
    Point3 viewportUpperLeft = cameraCenter - Vector3(0, 0, focalLength) - (viewportU / 2)
                               - (viewportV / 2);
    Point3 pixel00Location = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));

    // Rendering
    cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; i++)
    {
        // std::clog << "Scanlines remaining: " << (imageHeight - i) << '\r';
        cout.flush();

        for (int j = 0; j < imageWidth; j++)
        {
            Point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
            Vector3 rayDirection = pixelCenter - cameraCenter;

            Ray r(cameraCenter, rayDirection);

            Color pixelColor = RayColor(r, world);
            WriteColor(cout, pixelColor);
        }
    }

    std::clog << "Done.\n";

    return 0;
}