#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "3dvector.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(const Point3& cen, double rad, shared_ptr<Material> m) : center(cen), radius(rad), material_ptr(m) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    Point3 center;
    double radius;
    shared_ptr<Material> material_ptr;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    Vec3 oc = r.origin() - center;

    auto dir = r.direction();

    auto a = dot(dir, dir);
    auto b = 2 * dot(dir, oc);
    auto c = dot(oc, oc) - radius * radius;

    auto D = b * b - 4 * a * c;

    if (D < 0)
    {
        return false;
    }
    auto rootD = std::sqrt(D);

    auto ret = (-b - rootD) / (2 * a);

    if ((ret < t_min) || (ret > t_max))
        ret = (-b + rootD) / (2 * a);

    if ((ret < t_min) || (ret > t_max))
        return false;

    rec.t = ret;
    rec.p = r.t_length_in_dir(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_ptr;

    return true;

}

#endif