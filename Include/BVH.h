#ifndef BVH_H
#define BVH_H

#include <algorithm>

#include "Hittable.h"
#include "HittableList.h"
#include "RTWeekend.h"

class BVHNode : public Hittable
{
  public:
    BVHNode(HittableList const& list) : BVHNode(list.objects, 0, list.objects.size()) {}

    BVHNode(std::vector<shared_ptr<Hittable>> const& srcObjects, size_t start, size_t end)
    {
        auto objects = srcObjects;  // modifiable array of the source scene objects

        int axis = RandomInt(0, 2);

        auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

        size_t objectSpan = end - start;

        if (objectSpan == 1)
        {
            left = right = objects[start];
        }
        else if (objectSpan == 2)
        {
            if (comparator(objects[start], objects[start + 1]))
            {
                left = objects[start];
                right = objects[start + 1];
            }
            else
            {
                left = objects[start + 1];
                right = objects[start];
            }
        }
        else
        {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            size_t mid = start + objectSpan / 2;

            left = make_shared<BVHNode>(objects, start, mid);
            right = make_shared<BVHNode>(objects, mid, end);
        }

        bBox = AABB(left->BoundingBox(), right->BoundingBox());
    }

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

    static bool BoxCompare(shared_ptr<Hittable> const a, shared_ptr<Hittable> const b, int axisIndex)
    {
        return a->BoundingBox().Axis(axisIndex).min < b->BoundingBox().Axis(axisIndex).min;
    }

    static bool BoxXCompare(shared_ptr<Hittable> const a, shared_ptr<Hittable> const b)
    {
        return BoxCompare(a, b, 0);
    }

    static bool BoxYCompare(shared_ptr<Hittable> const a, shared_ptr<Hittable> const b)
    {
        return BoxCompare(a, b, 1);
    }

    static bool BoxZCompare(shared_ptr<Hittable> const a, shared_ptr<Hittable> const b)
    {
        return BoxCompare(a, b, 2);
    }
};

#endif