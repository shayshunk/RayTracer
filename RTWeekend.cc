#include "RTWeekend.h"

#include <cmath>
#include <iostream>
#include <string>

#include "Camera.h"

using std::cout, std::string;

Color RayColor(Ray const& r, Hittable const& world)
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

int main(int argc, char* argv[])
{
    // Defaults
    int imageWidth = 800;
    int samples = 25;
    int depth = 10;

    // Using command line arguments for setting render quality
    for (int i = 0; i < argc; i++)
    {
        if (string(argv[i]) == "-Size" && i + 1 < argc)
            imageWidth = std::stoi(argv[i + 1]);
        else if (string(argv[i]) == "-Depth" && i + 1 < argc)
            depth = std::stoi(argv[i + 1]);
        else if (string(argv[i]) == "-Samples" && i + 1 < argc)
            samples = std::stoi(argv[i + 1]);
    }

    // World
    HittableList world;

    auto groundMaterial = make_shared<Lambertian>(Color(0.1, 0.1, 0.8));
    auto centerMaterial = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto leftMaterial = make_shared<Dielectric>(1.5, Color(0.95, 0.95, 0.95));
    auto rightMaterial = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.01);

    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, groundMaterial));
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, centerMaterial));
    world.Add(make_shared<Sphere>(Point3(-1, 0, -1), 0.5, leftMaterial));
    world.Add(make_shared<Sphere>(Point3(-1, 0, -1), -0.4, leftMaterial));
    world.Add(make_shared<Sphere>(Point3(1, 0, -1), 0.5, rightMaterial));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = imageWidth;
    camera.samplesPerPixel = samples;
    camera.maxDepth = depth;

    camera.verticalFOV = 90;
    camera.lookFrom = Point3(-2, 2, 1);
    camera.lookAt = Point3(0, 0, -1);
    camera.vUp = Vector3(0, 1, 0);

    camera.Render(world);

    return 0;
}