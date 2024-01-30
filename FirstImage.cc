#include <cmath>
#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

using std::cout;

float HitSphere(Point3 const& center, float radius, Ray const& r)
{
    Vector3 oc = r.Origin() - center;

    float a = r.Direction().LengthSquared();
    float half_b = Dot(oc, r.Direction());
    float c = oc.LengthSquared() - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

Color RayColor(Ray const& r)
{
    float t = HitSphere(Point3(0, 0, -1), 0.5, r);

    if (t > 0)
    {
        Vector3 N = UnitVector(r.at(t) - Vector3(0, 0, -1));
        return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    Vector3 unitDirection = UnitVector(r.Direction());
    float a = 0.5 * (unitDirection.y()) + 1.0;
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
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
            Point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
            Vector3 rayDirection = pixelCenter - cameraCenter;

            Ray r(cameraCenter, rayDirection);

            Color pixelColor = RayColor(r);
            WriteColor(cout, pixelColor);
        }
    }

    std::clog << "Done.\n";

    return 0;
}