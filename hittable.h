#ifndef HITTABLE_H
#define HITTABLE_H

//#include "ray.h"
//#include "material.h"

#include "rt_project.h"

class Material;

struct hit_record
{
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> material_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {

        // if this dot product is less than 0, means the ray is hitting from outside the object, 
        // i.e, the ray is hitting on the front face of the object
        // otherwise the ray is inside, and hitting the inner face of the object
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
#endif