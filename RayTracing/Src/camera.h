#pragma once

#include "ray.h"

class Camera
{
private:
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
public:
    Camera()
    {        
        lowerLeftCorner = Vec3(-2.0, -1.0, -1.0);
        origin = Vec3(0.0, 0.0, 0.0);

        horizontal = Vec3(4.0, 0.0, 0.0);
        vertical = Vec3(0.0, 2.0, 0.0);
    }
    
    Ray GetRay(double u, double v) const
    {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
    }
};