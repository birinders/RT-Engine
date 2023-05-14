#ifndef RAY_H
#define RAY_H

#include "3dvector.h"

class Ray
{

public:
    Ray() {}
    Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

    Point3 origin() const { return orig; }
    Vec3 direction() const { return dir; }

    Point3 t_length_in_dir(double t) const
    {
        return orig + t * dir;
    }

public:
    Point3 orig;
    Vec3 dir;
};

#endif