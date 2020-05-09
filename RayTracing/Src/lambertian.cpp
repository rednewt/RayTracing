#include "material.h"
#include "utility.h"

bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, Vec3& outattenuation, Ray& outScattered) const
{
	Vec3 target =  record.hitPoint + record.normal + Utility::RandomVec3UnitSphere();
	
	outattenuation = diffuse;
	outScattered = Ray(record.hitPoint, target - record.hitPoint);

	return true;
}