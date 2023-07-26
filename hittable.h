#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
struct hit_record{
    // 相交点
    vec3 p;
    // 法向量
    vec3 normal;
    // 相交距离光线的参数
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r,const vec3& outward_normal){
        // 如果光线与法向量的夹角小于90度，则为正面，说明光线与法向量的方向相同
        front_face = dot(r.direction(),outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable{
    public:
        virtual bool hit(const ray& r,double t_min,double t_max,hit_record& rec) const = 0;
};
#endif