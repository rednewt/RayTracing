#pragma once

#include "ray.h"
#include <vector>

struct HitRecord
{
	Vec3 normal;
	Vec3 hitPoint;
	bool frontFace;
	double t;

	void setFaceNormal(const Ray& ray, const Vec3& outwardNormal)
	{
		frontFace = VectorDot(ray.direction, outwardNormal) < 0;
		
		if (frontFace)
			normal = outwardNormal;
		else
			normal = -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& ray, double t_min, double t_max, HitRecord& outRecord) const = 0;
};


class HittableList : public Hittable
{
public:
	std::vector<std::shared_ptr<Hittable>> pObjects;
public:
	HittableList() = default; 
	
	void Clear() { pObjects.clear(); }
	void Add(std::shared_ptr<Hittable> pObj) { pObjects.push_back(pObj); }
	
	bool Hit(const Ray& ray, double t_min, double t_max, HitRecord& outRecord) const override;
};