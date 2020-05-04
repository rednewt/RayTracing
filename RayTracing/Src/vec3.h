#pragma once

#include <iostream>

class Vec3
{
public:
	double x;
	double y;
	double z;

public:
	Vec3(double ix, double iy, double iz) : x(ix), y(iy), z(iz) {}
	Vec3() : x(0), y(0), z(0) {}

	Vec3 operator-() const { return Vec3(-x, -y, -z);  }

	Vec3& operator+=(const Vec3& rhs) 
	{ 
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vec3& operator-=(const Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	Vec3& operator*=(const double t)
	{
		x *= t;
		y *= t;
		z *= t;

		return *this;
	}

	Vec3& operator/=(const double t)
	{
		return (*this *= 1 / t);
	}

	double LengthSquared() const
	{
		return x*x + y*y + z*z;
	}

	double Length() const
	{
		return sqrt(LengthSquared());
	}
	
	void WriteColor(std::ostream& out)
	{
		out << static_cast<int>(255.999 * x) << ' '
			<< static_cast<int>(255.999 * y) << ' '
			<< static_cast<int>(255.999 * z) << '\n';
	}
};

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) 
{
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator*(const Vec3& a, const Vec3& b)
{
	return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline Vec3 operator*(const Vec3& v, double t)
{
	return Vec3(v.x * t, v.y * t, v.z * t);
}

inline Vec3 operator*(double t, const Vec3& v)
{
	return v * t;
}

inline Vec3 operator/(const Vec3& v, double t)
{
	return v * (1 / t);
}

inline double VectorDot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x
		 + a.y * b.y
		 + a.z * b.z;
}

inline Vec3 VectorCross(const Vec3& a, const Vec3& b)
{
	return Vec3(a.y*b.z - a.z*b.y, 
				a.z*b.x - a.x*b.z, 
				a.x*b.y - a.y*b.x);
}

inline Vec3 VectorNormalize(Vec3 v)
{
	return v / v.Length();
}