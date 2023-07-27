#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(vec3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;

public:
    vec3 center;
    double radius;
    shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    // 计算光线到球心的向量
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    // 如果没有击中，则返回false
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    // 找到最近的根，该根在允许的范围内
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }
    rec.t = root;
    // 计算交点的位置
    rec.p = r.at(rec.t);
    // 计算交点处的法向量
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    return true;
}
#endif
