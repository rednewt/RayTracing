#include "hittable.h"

bool HittableList::Hit(const Ray& ray, double t_min, double t_max, HitRecord& outRecord) const
{
	bool hitAnything = false;
	double closest_t = t_max;

	HitRecord r;
	for (auto const& obj : pObjects)
	{
		if (obj->Hit(ray, t_min, closest_t, r))
		{
			hitAnything = true;
			closest_t = r.t;
		}
	}
	
	outRecord = r;

	return hitAnything;
}
