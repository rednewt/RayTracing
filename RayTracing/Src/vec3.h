#pragma once

#include <math.h>

class vec3
{
public:
	double x;
	double y;
	double z;

public:
	vec3(double ix, double iy, double iz) : x(ix), y(iy), z(iz) {}
	vec3() : x(0), y(0), z(0) {}

	vec3 operator-() const { return vec3(-x, -y, -z);  }

	vec3& operator+=(const vec3& rhs) 
	{ 
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	vec3& operator-=(const vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	vec3& operator*=(const double t)
	{
		x *= t;
		y *= t;
		z *= t;

		return *this;
	}

	vec3 operator/=(const double t)
	{
		return (*this *= 1 / t);
	}

	double length_squared() const
	{
		return x*x + y*y + z*z;
	}

	double length() const
	{
		return sqrt(length_squared());
	}

};