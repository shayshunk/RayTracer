#include "RTWeekend.h"

#include <cmath>
#include <iostream>

#include "Camera.h"

using std::cout;

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

int main()
{
    // World
    HittableList world;

    auto groundMaterial = make_shared<Lambertian>(Color(0.8, 0.8, 0));
    auto centerMaterial = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto leftMaterial = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.01);
    auto rightMaterial = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.08);

    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100, groundMaterial));
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5, centerMaterial));
    world.Add(make_shared<Sphere>(Point3(-1.0, 0, -1), 0.5, leftMaterial));
    world.Add(make_shared<Sphere>(Point3(1.0, 0, -1), 0.5, rightMaterial));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 800;
    camera.samplesPerPixel = 100;
    camera.maxDepth = 25;

    camera.Render(world);

    return 0;
}