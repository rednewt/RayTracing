#include "sphere.h"

Sphere sp = Sphere(Vec3(0, 0, -4), 2);

Vec3 RayColor(const Ray& ray)
{
    HitRecord r;
  
    if (sp.Hit(ray, 0, DBL_MAX, r))
    {
        return 0.5 * (r.normal + Vec3(1.0, 1.0, 1.0));
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
