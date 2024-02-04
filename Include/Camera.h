#ifndef CAMERA_H
#define CAMERA_H

#include "RTWeekend.h"

using std::cout;

class Camera
{
  public:
    double aspectRatio = 1;  // Ratio of image width over height
    int imageWidth = 100;  // Rendered image width in pixels
    int samplesPerPixel = 10;  // Count of random samples per pixel (AA)
    int maxDepth = 10;  // Maximum number of ray bounces

    double verticalFOV = 90;  // Vertical field of view
    Point3 lookFrom = Point3(0, 0, -1);  // Point camera is looking from
    Point3 lookAt = Point3(0, 0, 0);  // Point camera is looking at
    Vector3 vUp = Vector3(0, 1, 0);  // Relative camera "up" direction

    double defocusAngle = 0;  // Variation angle of rays through each pixel
    double focusDistance = 10;  // Distance from camera center to plane of perfect focus

    void Render(Hittable const& world)
    {
        Initialize();

        cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int i = 0; i < imageHeight; i++)
        {
            std::clog << "\rScanlines remaining: " << (imageHeight - i) << "/" << imageHeight;
            cout.flush();

            for (int j = 0; j < imageWidth; j++)
            {
                Color pixelColor(0, 0, 0);

                for (int sample = 0; sample < samplesPerPixel; sample++)
                {
                    Ray r = GetRay(i, j);
                    pixelColor += RayColor(r, maxDepth, world);
                }

                WriteColor(cout, pixelColor, samplesPerPixel);
            }
        }

        std::clog << "\nDone.                           \n";
    }

  private:
    int imageHeight;  // Rendered image height in pixels
    Point3 center;  // Camera center
    Point3 pixel00Location;  // Location of pixel 0, 0 (top left)
    Vector3 pixelDeltaU;  // Offset to pixel to get to the next one on right
    Vector3 pixelDeltaV;  // Offset to pixel to get to the next one below
    Vector3 u, v, w;  // Camera frame's basis vectors
    Vector3 defocusDiskU;  // Defocus disk horizontal radius
    Vector3 defocusDiskV;  // Defocus disk vertical radius

    void Initialize()
    {
        // Calculating image height and checking that it's >= 1
        imageHeight = static_cast<int>(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        // Setting up Camera and Viewport
        center = lookFrom;

        double theta = DegreesToRadians(verticalFOV);
        double height = tan(theta / 2);

        double viewportHeight = 2.0 * height * focusDistance;
        double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

        // Calculating basis vectors for the camera frame
        w = UnitVector(lookFrom - lookAt);
        u = UnitVector(Cross(vUp, w));
        v = Cross(w, u);

        // Calculating vectors across the horizontal and down the vertical viewport edges Vector3
        Vector3 viewportU(viewportWidth * u);  // Horizontal viewport vector
        Vector3 viewportV(viewportHeight * -v);  // Vertical viewport vector

        // Calculating horizontal and vertical delta vectors from pixel to pixel
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        // Calculating the location of the upper left pixel
        Point3 viewportUpperLeft = center - (focusDistance * w) - (viewportU / 2) - (viewportV / 2);
        pixel00Location = viewportUpperLeft + (0.5 * (pixelDeltaU + pixelDeltaV));

        // Calculating camera defocus disk basis vectors
        double defocusRadius = focusDistance * tan(DegreesToRadians(defocusAngle / 2));
        defocusDiskU = u * defocusRadius;
        defocusDiskV = v * defocusRadius;
    }

    Ray GetRay(int i, int j) const
    {
        // Get a randomly sampled camera ray for pixel (i, j) from camera defocus disk
        Point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
        Point3 pixelSample = pixelCenter + PixelSampleSquare();

        Point3 rayOrigin = (defocusAngle <= 0) ? center : DefocusDiskSample();
        Vector3 rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    Vector3 PixelSampleSquare() const
    {
        // Return a random point in the square surround the pixel at the origin
        double px = -0.5 + RandomDouble();
        double py = -0.5 + RandomDouble();

        return (px * pixelDeltaU) + (py * pixelDeltaV);
    }

    Point3 DefocusDiskSample() const
    {
        // Returns a random point in the camera defocus disk
        Vector3 p = RandomInUnitDisk();

        return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
    }

    Color RayColor(Ray const& r, int depth, Hittable const& world) const
    {
        // No more light gathering if we hit max depth
        if (depth == 0)
            return Color(0, 0, 0);

        HitRecord rec;

        if (world.Hit(r, Interval(0.001, infinity), rec))
        {
            Ray scattered;
            Color attenuation;

            if (rec.material->Scatter(r, rec, attenuation, scattered))
                return attenuation * RayColor(scattered, depth - 1, world);

            return Color(0, 0, 0);
        }

        Vector3 unitDirection = UnitVector(r.Direction());
        double a = 0.5 * (unitDirection.y()) + 1.0;
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }
};

#endif