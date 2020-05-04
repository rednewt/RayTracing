#pragma once

#include "vec3.h"

class Ray
{
public:
	Vec3 origin;
	Vec3 direction;

public:
	Ray() {}
	Ray(const Vec3& iorigin, const Vec3& idirection) : origin(iorigin), direction(idirection) {}

	Vec3 At(double t) const
	{
		return origin + t * direction;
	}
};