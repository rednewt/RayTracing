#pragma once

#include "hittable.h"

class Sphere : public Hittable
{
public:
	Vec3 center;
	double radius;

public:
	Sphere() = default;
	Sphere(const Vec3& icenter, double iradius) : center(icenter), radius(iradius) {}

	bool Hit(const Ray& ray, double t_min, double t_max, HitRecord& outRecord) const override;
};