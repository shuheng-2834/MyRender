#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

/// @brief 判断光线是否击中球体
/// @param center 球心
/// @param radius 半径
/// @param r 光线
/// @return 是否击中
double hit_sphere(const vec3 &center, double radius, const ray &r)
{
    // 计算光线到球心的向量
    vec3 oc = r.origin() - center;
    // 计算光线与光线的点乘
    auto a = dot(r.direction(), r.direction());
    // 计算光线与球心的点乘，两倍
    auto b = 2.0 * dot(oc, r.direction());
    // 计算光线与球心的点乘，减去半径的平方
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

vec3 ray_color(const ray &r)
{
    auto t = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0)
    {
        vec3 n = unit_vector(r.at(t) - vec3(0, 0, -1));
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