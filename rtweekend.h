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

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif