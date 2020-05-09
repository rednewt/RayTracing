#pragma once

#include <cstdlib>

namespace Utility
{
    inline double RandomDouble()
    {
        return rand() / (RAND_MAX + 1.0);
    }

    inline double RandomDouble(double min, double max)
    {
        return min + (max - min) * RandomDouble();
    }

    inline double Clamp(double x, double min, double max) 
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    inline Vec3 RandomVec3()
    {
        return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    inline Vec3 RandomVec3(double min, double max)
    {
        return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    inline Vec3 RandomVec3UnitSphere()
    {
        Vec3 random;
        do
        {
            random = RandomVec3(-1, 1);
        } while (random.LengthSquared() >= 1); 

        return random;
    }

    inline Vec3 RandomVec3HemiSphere(const Vec3& normal)
    {
        Vec3 random = RandomVec3UnitSphere();

        if (VectorDot(random, normal) > 0.0)
            return random;
        else
            return -random;
    }

    inline void WriteColor(std::ostream& out, Vec3 color, uint16_t sampleCount)
    {
        double scale = 1.0 / sampleCount;

        color *= scale;
        color = Vec3(sqrt(color.x), sqrt(color.y), sqrt(color.z));

        out << static_cast<int>(256 * Utility::Clamp(color.x, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utility::Clamp(color.y, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utility::Clamp(color.z, 0.0, 0.999)) << '\n';
    }
}