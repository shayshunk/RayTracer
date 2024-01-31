#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
  public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { Add(object); }

    void Clear() { objects.clear(); }

    void Add(shared_ptr<Hittable> object) { objects.push_back(object); }

    bool Hit(Ray const& r, double rayTMin, double rayTMax, HitRecord& rec) const override
    {
        HitRecord tempRec;
        bool hitAnything = false;

        double closestSoFar = rayTMax;

        for (auto const& object : objects)
        {
            if (object->Hit(r, rayTMin, closestSoFar, tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }
};

#endif