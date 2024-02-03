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

        double refractionRatio = rec.frontFace ? (1.0 / ir) : ir;

        Vector3 unitDirection = UnitVector(rIn.Direction());

        double cosTheta = fmin(Dot(-unitDirection, rec.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = (refractionRatio * sinTheta) > 1.0;

        Vector3 direction;

        if (cannotRefract || (Reflectance(cosTheta, refractionRatio) > RandomDouble()))
            direction = Reflect(unitDirection, rec.normal);
        else
            direction = Refract(unitDirection, rec.normal, refractionRatio);

        scattered = Ray(rec.p, direction);

        return true;
    }

  private:
    double ir;  // Index of refraction

    static double Reflectance(double cos, double refRatio)
    {
        // Using Schlick's approximation for reflectance
        double r0 = (1 - refRatio) / (1 + refRatio);
        r0 *= r0;

        return r0 + (1 - r0) * pow((1 - cos), 5);
    }
};

#endif