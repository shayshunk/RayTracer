#include "RTWeekend.h"

#include <cmath>
#include <iostream>

#include "Camera.h"
#include "Color.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

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

    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -100.5, 1), 100));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 100;

    camera.Render(world);

    return 0;
}