#include "ray.h"

bool HitSphere(const Vec3& sphereCenter, const Ray& ray, double sphereRadius)
{
    auto oc = ray.origin - sphereCenter;
    
    auto a = ray.direction.LengthSquared();
    auto b = 2.0 * VectorDot(ray.direction, oc);
    auto c = oc.LengthSquared() - sphereRadius * sphereRadius;
    
    return b*b - 4*a*c > 0;
}


Vec3 RayColor(const Ray& ray)
{
    if (HitSphere(Vec3(0.0, 0.0, -1.0), ray, 0.5))
        return Vec3(1.0, 0.0, 0.0);

    Vec3 normalized = VectorNormalize(ray.direction);
    double y = 0.5 * (normalized.y + 1.0); //convert to [0,1] from [-1, 1]
    
    Vec3 colorA = Vec3(1.0, 1.0, 1.0);
    Vec3 colorB = Vec3(0.5, 0.7, 1.0);

    return colorA + (colorB - colorA) * y;
}


int main() 
{
    const int canvasWidth = 200;
    const int canvasHeight = 100;

    std::cout << "P3\n" << canvasWidth << ' ' << canvasHeight << "\n255\n";

    Vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    for (int j = canvasHeight-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < canvasWidth; ++i) 
        {
            auto u = static_cast<double>(i) / canvasWidth;
            auto v = static_cast<double>(j) / canvasHeight;

            Ray r = Ray(origin, lowerLeftCorner + u * horizontal + v * vertical);

            RayColor(r).WriteColor(std::cout);
        }
    }

    std::cerr << "\nDone\n";

}
