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
    Metal(Color const& a) : albedo(a) {}

    bool
    Scatter(Ray const& rIn, HitRecord const& rec, Color& attenuation, Ray& scattered) const override
    {
        Vector3 reflected = Reflect(UnitVector(rIn.Direction()), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;

        return true;
    }

  private:
    Color albedo;
};

#endif