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

    inline void WriteColor(std::ostream& out, Vec3 color, uint16_t sampleCount)
    {
        double scale = 1.0 / sampleCount;

        color *= scale;

        out << static_cast<int>(256 * Utility::Clamp(color.x, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utility::Clamp(color.y, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Utility::Clamp(color.z, 0.0, 0.999)) << '\n';
    }
}