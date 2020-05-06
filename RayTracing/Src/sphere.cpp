#include "sphere.h"

bool Sphere::Hit(const Ray& ray, double t_min, double t_max, HitRecord& outRecord) const
{
    auto oc = ray.origin - center;

    //solves quadratic equation of ray-sphere intersection (simplified)
    auto a = ray.direction.LengthSquared();
    auto half_b = VectorDot(ray.direction, oc);
    auto c = oc.LengthSquared() - radius * radius;

    auto D = half_b * half_b - a * c;

    if (D < 0)
        return false;

    auto t = (-half_b - sqrt(D)) / a;
    
    if (t > t_min && t < t_max)
    {
        outRecord.t = t;
        outRecord.hitPoint = ray.At(t);

        Vec3 normal = (outRecord.hitPoint - center) / radius;
        outRecord.setFaceNormal(ray, normal);

        return true;
    }
    
    t = (-half_b + sqrt(D)) / a;

    if (t > t_min && t < t_max)
    {
        outRecord.t = t;
        outRecord.hitPoint = ray.At(t);

        Vec3 normal = (outRecord.hitPoint - center) / radius;
        outRecord.setFaceNormal(ray, normal);


        return true;
    }

	return false;
}
