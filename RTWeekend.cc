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

    double R = cos(pi / 4);

    auto leftMaterial = make_shared<Lambertian>(Color(0, 0, 1));
    auto rightMaterial = make_shared<Lambertian>(Color(1, 0, 0));

    world.Add(make_shared<Sphere>(Point3(-R, 0, -1), R, leftMaterial));
    world.Add(make_shared<Sphere>(Point3(R, 0, -1), R, rightMaterial));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 800;
    camera.samplesPerPixel = 50;
    camera.maxDepth = 25;

    camera.verticalFOV = 90;

    camera.Render(world);

    return 0;
}