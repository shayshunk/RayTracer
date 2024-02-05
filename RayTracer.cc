#include <cmath>
#include <iostream>
#include <string>

#include "Camera.h"
#include "RTWeekend.h"

using std::cout, std::string;

int main(int argc, char* argv[])
{
    // Defaults
    int imageWidth = 800;
    int samples = 25;
    int depth = 50;
    int fieldOfView = 20;
    Vector3 lookFrom(13, 2, 3);
    Ray r;

    // Using command line arguments for setting render quality
    for (int i = 0; i < argc; i++)
    {
        if (string(argv[i]) == "-Size" && i + 1 < argc)
            imageWidth = std::stoi(argv[i + 1]);
        else if (string(argv[i]) == "-Depth" && i + 1 < argc)
            depth = std::stoi(argv[i + 1]);
        else if (string(argv[i]) == "-Samples" && i + 1 < argc)
            samples = std::stoi(argv[i + 1]);
        else if (string(argv[i]) == "-FOV" && i + 1 < argc)
            fieldOfView = std::stoi(argv[i + 1]);
        else if (string(argv[i]) == "-CameraPos" && i + 3 < argc)
            lookFrom
                = Vector3(std::stoi(argv[i + 1]), std::stoi(argv[i + 2]), std::stoi(argv[i + 3]));
    }

    // World
    HittableList world;

    auto groundMaterial = make_shared<Lambertian>(Color(0.1, 0.1, 0));
    world.Add(make_shared<Sphere>(Point3(0, -1000, -1), 1000, groundMaterial));

    for (int a = 0; a < 11; a++)
    {
        for (int b = 0; b < 11; b++)
        {
            double chooseMaterial = RandomDouble();

            Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
            {
                shared_ptr<Material> sphereMaterial;

                if (chooseMaterial < 0.5)  // Diffuse
                {
                    Color albedo = Color::Random() * Color::Random();

                    sphereMaterial = make_shared<Lambertian>(albedo);
                }
                else if (chooseMaterial < 0.75)
                {
                    Color albedo = Color::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.4);

                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                }
                else  // Glass
                {
                    Color albedo = Color::Random(0.8, 1);
                    sphereMaterial = make_shared<Dielectric>(1.5, albedo);
                }

                world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
            }
        }
    }

    auto backMaterial = make_shared<Lambertian>(Color(0.8, 0.1, 0.1));
    auto middleMaterial = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.03);
    auto frontMaterial = make_shared<Dielectric>(1.33, Color(0.95, 0.95, 0.8));

    world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, backMaterial));
    world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, middleMaterial));
    world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, frontMaterial));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = imageWidth;
    camera.samplesPerPixel = samples;
    camera.maxDepth = depth;

    camera.verticalFOV = fieldOfView;
    camera.lookFrom = lookFrom;
    camera.lookAt = Point3(0, 0, 0);
    camera.vUp = Vector3(0, 1, 0);

    camera.defocusAngle = 0.6;
    camera.focusDistance = 10;

    camera.Render(world);

    return 0;
}