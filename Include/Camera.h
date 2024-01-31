#ifndef CAMERA_H
#define CAMERA_H

#include "Color.h"
#include "Hittable.h"
#include "RTWeekend.h"

using std::cout;

class Camera
{
  public:
    double aspectRatio = 1;  // Ratio of image width over height
    int imageWidth = 100;  // Rendered image width in pixels

    void Render(Hittable const& world)
    {
        Initialize();

        cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int i = 0; i < imageHeight; i++)
        {
            // std::clog << "Scanlines remaining: " << (imageHeight - i) << '\r';
            cout.flush();

            for (int j = 0; j < imageWidth; j++)
            {
                Point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
                Vector3 rayDirection = pixelCenter - center;

                Ray r(center, rayDirection);

                Color pixelColor = RayColor(r, world);
                WriteColor(cout, pixelColor);
            }
        }

        std::clog << "Done.\n";
    }

  private:
    int imageHeight;  // Rendered image height in pixels
    Point3 center;  // Camera center
    Point3 pixel00Location;  // Location of pixel 0, 0 (top left)
    Vector3 pixelDeltaU;  // Offset to pixel to get to the next one on right
    Vector3 pixelDeltaV;  // Offset to pixel to get to the next one below

    void Initialize()
    {
        // Calculating image height and checking that it's >= 1
        imageHeight = static_cast<int>(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        // Setting up Camera and Viewport
        double focalLength = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

        center = Point3(0, 0, 0);

        // Calculating vectors across the horizontal and down the vertical viewport edges Vector3
        Vector3 viewportU(viewportWidth, 0, 0);
        Vector3 viewportV(0, -viewportHeight, 0);

        // Calculating horizontal and vertical delta vectors from pixel to pixel
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        // Calculating the location of the upper left pixel
        Point3 viewportUpperLeft = center - Vector3(0, 0, focalLength) - (viewportU / 2)
                                   - (viewportV / 2);
        pixel00Location = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));
    }

    Color RayColor(Ray const& r, Hittable const& world) const
    {
        HitRecord rec;
        if (world.Hit(r, Interval(0, infinity), rec))
        {
            return 0.5 * (rec.normal + Color(1, 1, 1));
        }

        Vector3 unitDirection = UnitVector(r.Direction());
        double a = 0.5 * (unitDirection.y()) + 1.0;
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }
};

#endif