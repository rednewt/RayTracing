#include "materials.h"
#include "utility.h"

bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, Vec3& outattenuation, Ray& outScattered) const
{
	Vec3 target =  record.hitPoint + record.normal + Utility::RandomVec3UnitSphere();
	
	outattenuation = diffuse;
	outScattered = Ray(record.hitPoint, target - record.hitPoint);

	return true;
}

bool Metal::Scatter(const Ray& ray, const HitRecord& record, Vec3& outattenuation, Ray& outScattered) const
{
	Vec3 reflected = Utility::ReflectVec3(VectorNormalize(ray.direction), record.normal);

	outattenuation = specular;
	outScattered = Ray(record.hitPoint, reflected + fuzziness*Utility::RandomVec3UnitSphere() );

	return VectorDot(outScattered.direction, record.normal) > 0.0;
}
