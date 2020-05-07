#include "sphere.h"
#include "camera.h"
#include "utility.h"

Vec3 RayColor(const Ray& ray, const Hittable& world)
{
    HitRecord r;
    if (world.Hit(ray, 0, DBL_MAX, r))
        return 0.5 * (r.normal + Vec3(1.0, 1.0, 1.0));
    
    Vec3 normalized = VectorNormalize(ray.direction);
    double y = 0.5 * (normalized.y + 1.0); //convert to [0,1] from [-1, 1]
    
    Vec3 colorA = Vec3(1.0, 1.0, 1.0);
    Vec3 colorB = Vec3(0.5, 0.7, 1.0);

    return colorA + (colorB - colorA) * y;
}


constexpr int g_canvasWidth = 800;
constexpr int g_canvasHeight = 400;
constexpr int g_sampleCount = 20;

int main() 
{

    std::cout << "P3\n" << g_canvasWidth << ' ' << g_canvasHeight << "\n255\n";


    HittableList world;
    Camera camera;
    
    world.Add( std::make_shared<Sphere>( Vec3(0, 0, -1), 0.5) );
    world.Add( std::make_shared<Sphere>( Vec3(0, -100.5, -1), 100) );

    for (int j = g_canvasHeight-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < g_canvasWidth; ++i) 
        {
            Vec3 pixelColor;
            for (int k = 0; k < g_sampleCount; ++k)
            {
                auto u = static_cast<double>(i + Utility::RandomDouble()) / g_canvasWidth;
                auto v = static_cast<double>(j + Utility::RandomDouble()) / g_canvasHeight;
                
                Ray r = camera.GetRay(u, v);
                pixelColor += RayColor(r, world);
            }

            Utility::WriteColor(std::cout, pixelColor, g_sampleCount);
        }
    }

    std::cerr << "\nDone\n";

}
