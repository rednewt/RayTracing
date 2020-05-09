#pragma once

#include "hittable.h"

class Material; 

class Sphere : public Hittable
{
public:
	Vec3 center;
	double radius;
	std::shared_ptr<Material> materialPtr;
public:
	Sphere() = default;
	Sphere(const Vec3& icenter, double iradius, std::shared_ptr<Material> matptr) : 
		center(icenter), radius(iradius), materialPtr(matptr) {}

	bool Hit(const Ray& ray, double t_min, double t_max, HitRecord& outRecord) const override;
};