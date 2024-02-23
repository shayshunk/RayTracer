#ifndef BVH_H
#define BVH_H

#include "Hittable.h"
#include "HittableList.h"
#include "RTWeekend.h"

class BVHNode : public Hittable
{
  public:
    BVHNode(HittableList const& list) : BVHNode(list.objects, 0, list.objects.size()) {}

    BVHNode(std::vector<shared_ptr<Hittable>> const& srcObjects, size_t start, size_t end) {}

    bool Hit(Ray const& r, Interval rayT, HitRecord& rec) const override
    {
        if (!bBox.Hit(r, rayT))
            return false;

        bool hitLeft = left->Hit(r, rayT, rec);
        bool hitRight = right->Hit(r, Interval(rayT.min, hitLeft ? rec.t : rayT.max), rec);

        return hitLeft || hitRight;
    }

    AABB BoundingBox() const override { return bBox; }

  private:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    AABB bBox;
};

#endif