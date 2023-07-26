#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

/// @brief 判断光线是否击中球体
/// @param center 球心
/// @param radius 半径
/// @param r 光线
/// @return 被击中球体的T值，距离光线起点的距离，如果没有击中，则返回-1
double hit_sphere(const vec3 &center, double radius, const ray &r)
{
    // 计算光线到球心的向量
    vec3 oc = r.origin() - center;
    // 计算光线与光线的点乘
    auto a = r.direction().length_squared();
    // 计算光线与球心的点乘，两倍
    auto half_b = dot(oc, r.direction());
    // 计算光线与球心的点乘，减去半径的平方
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

vec3 ray_color(const ray &r)
{
    // 返回被击中的球体的t值，距离光线起点的距离，
    auto t = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0)
    {
        // 计算与球体交点处的球面法向量
        vec3 n = unit_vector(r.at(t) - vec3(0, 0, -1));
        // 返回交点处的颜色，我们将向量的每个分量都映射到[0，1]的范围，然后乘以0.5,最后的颜色范围将在[0,0.5]
        return 0.5 * vec3(n.x() + 1, n.y() + 1, n.z() + 1);
    }
    // 获取单位向量
    vec3 unit_direction = unit_vector(r.direction());
    // 将 y 值映射到 [0, 1]
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}