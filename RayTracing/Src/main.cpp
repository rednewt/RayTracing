#include "sphere.h"
#include "camera.h"
#include "utility.h"
#include "materials.h"

Vec3 RayColor(const Ray& ray, const Hittable& world, int depth)
{
    if (depth <= 0)
        return Vec3(0, 0, 0);

    HitRecord r;
    if (world.Hit(ray, 0.001, DBL_MAX, r))
    {
        Ray scattered;
        Vec3 att;

        if (r.materialPtr->Scatter(ray, r, att, scattered))
            return att * RayColor(scattered, world, depth - 1);
        
        return Vec3(0, 0, 0);
    }
    
    double lerpFactor = 0.5 * (VectorNormalize(ray.direction).y + 1.0); 
    
    Vec3 colorA = Vec3(1, 1, 1);
    Vec3 colorB = Vec3(0.5, 0.7, 1.0);

    return (1 - lerpFactor)*colorA + lerpFactor*colorB;
}


constexpr int g_canvasWidth = 800;
constexpr int g_canvasHeight = 400;
constexpr int g_sampleCount = 20;

int main() 
{

    std::cout << "P3\n" << g_canvasWidth << ' ' << g_canvasHeight << "\n255\n";

    HittableList world;
    Camera camera;
    
    world.Add( std::make_shared<Sphere>( Vec3(0, 0, -1), 0.5, std::make_shared<Lambertian>(Vec3(0.8, 0.5, 0.3))) );
    world.Add( std::make_shared<Sphere>( Vec3(0, -100.5, -1), 100, std::make_shared<Lambertian>(Vec3(0.7, 0.3, 0.3))) );

    world.Add(std::make_shared<Sphere>( Vec3(1, 0, -1), 0.5, std::make_shared<Metal>( Vec3(0.5, 0.5, 0.5), 0.1 ) ) );
    world.Add(std::make_shared<Sphere>( Vec3(-1, 0, -1), 0.5, std::make_shared<Metal>( Vec3(0.8, 0.8, 0.8), 1 ) ) );



    for (int j = g_canvasHeight-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < g_canvasWidth; ++i) 
        {
            Vec3 pixelColor;
            for (int k = 0; k < g_sampleCount; ++k)
            {
                auto u = static_cast<double>(i + Utility::RandomDouble()) / (g_canvasWidth - 1);
                auto v = static_cast<double>(j + Utility::RandomDouble()) / (g_canvasHeight - 1);
                
                Ray r = camera.GetRay(u, v);
                pixelColor += RayColor(r, world, 50);
            }

            Utility::WriteColor(std::cout, pixelColor, g_sampleCount);
        }
    }

    std::cerr << "\nDone\n";

}
