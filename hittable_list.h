#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record& rec) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec;
    // 定义是否击中任何物体
    bool hit_anything = false;
    // 定义最近的物体
    auto closest_so_far = t_max;
    // 遍历所有物体
    for (const auto &object : objects)
    {
        // 如果有击中物体，则更新最近的物体
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif