#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Hittable.h"
#include "Ray.h"

class HitRecord;

class Material
{
  public:
    virtual ~Material() = default;

    virtual bool
    Scatter(Ray const& rIn, HitRecord const& rec, Color& attenuation, Ray& scattered) const
        = 0;
};

class Lambertian : public Material
{
  public:
    Lambertian(Color const& a) : albedo(a) {}

    bool
    Scatter(Ray const& rIn, HitRecord const& rec, Color& attenuation, Ray& scattered) const override
    {
        Vector3 scatterDirection = rec.normal + RandomUnitVector();

        // Catch "degenerate" scatter direction (~0)
        if (scatterDirection.NearZero())
            scatterDirection = rec.normal;

        scattered = Ray(rec.p, scatterDirection);
        attenuation = albedo;

        return true;
    }

  private:
    Color albedo;
};

class Metal : public Material
{
  public:
    Metal(Color const& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool
    Scatter(Ray const& rIn, HitRecord const& rec, Color& attenuation, Ray& scattered) const override
    {
        Vector3 reflected = Reflect(UnitVector(rIn.Direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * RandomUnitVector());
        attenuation = albedo;

        return (Dot(scattered.Direction(), rec.normal) > 0);
    }

  private:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material
{
  public:
    Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

    bool
    Scatter(Ray const& rIn, HitRecord const& rec, Color& attenuation, Ray& scattered) const override
    {
        attenuation = Color(1, 1, 1);

        double refractionRatio = rec.frontFace ? (1.0, ir) : ir;

        Vector3 unitDirection = UnitVector(rIn.Direction());
        Vector3 refracted = Refract(unitDirection, rec.normal, refractionRatio);

        scattered = Ray(rec.p, refracted);

        return true;
    }

  private:
    double ir;  // Index of refraction
};

#endif