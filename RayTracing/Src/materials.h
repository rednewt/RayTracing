#pragma once

#include "hittable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& ray, const HitRecord& record, Vec3& outattenuation, Ray& outScattered) const = 0;
};

class Lambertian : public Material
{
public:
	Vec3 diffuse;
public:
	Lambertian(const Vec3& color) : diffuse(color) {}

	bool Scatter(const Ray& ray, const HitRecord& record, Vec3& outattenuation, Ray& outScattered) const override;
};


class Metal : public Material
{
public:
	Vec3 specular;
	double fuzziness;
public:
	Metal(const Vec3& color, double fuzz) : specular(color), fuzziness(fuzz < 1 ? fuzz : 1) {}

	bool Scatter(const Ray& ray, const HitRecord& record, Vec3& outattenuation, Ray& outScattered) const override;
};
