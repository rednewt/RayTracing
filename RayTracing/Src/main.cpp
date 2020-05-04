#include "ray.h"

double HitSphere(const Vec3& sphereCenter, const Ray& ray, double sphereRadius)
{
    auto oc = ray.origin - sphereCenter;
    
    //solves quadratic equation of ray-sphere intersection (simplified)
    auto a = ray.direction.LengthSquared();
    auto half_b = VectorDot(ray.direction, oc);
    auto c = oc.LengthSquared() - sphereRadius * sphereRadius;

    auto D = half_b*half_b - a*c;

    if (D < 0)
        return -1.0;

    return (-half_b - sqrt(D)) / a;
}


Vec3 RayColor(const Ray& ray)
{
    auto t = HitSphere(Vec3(0.0, 0.0, -1.0), ray, 0.5);

    if (t > 0.0)
    {
        Vec3 normal = VectorNormalize(ray.At(t) - Vec3(0.0, 0.0, -1.0));
        return 0.5 * (normal + Vec3(1.0, 1.0, 1.0));
    }
        
    Vec3 normalized = VectorNormalize(ray.direction);
    double y = 0.5 * (normalized.y + 1.0); //convert to [0,1] from [-1, 1]
    
    Vec3 colorA = Vec3(1.0, 1.0, 1.0);
    Vec3 colorB = Vec3(0.5, 0.7, 1.0);

    return colorA + (colorB - colorA) * y;
}


int main() 
{
    const int canvasWidth = 800;
    const int canvasHeight = 400;

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
