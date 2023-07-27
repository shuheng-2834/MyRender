#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

/// @brief 将角度转换为弧度
/// @param degrees 角度
/// @return 弧度
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double random_double()
{
    // 返回[0,1)之间的随机数
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    // 返回[min,max)之间的随机数
    return min + (max - min) * random_double();
}
/// @brief 限制x的范围在[min,max]之间
/// @param x 输入的值
/// @param min 最小值
/// @param max 最大值
/// @return 返回限制后的值
inline double clamp(double x,double min,double max){
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif