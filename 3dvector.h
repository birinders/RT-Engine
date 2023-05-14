#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <fstream>

using std::sqrt;

class Vec3
{
public:
    Vec3() : e{ 0, 0, 0 } {}
    Vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vec3& operator+=(const Vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(const Vec3& v)
    {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    Vec3& operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double length() const { return sqrt(squared_length()); }

    double squared_length() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool near_zero() const {
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }


public:
    double e[3];
};

using Point3 = Vec3;
using Color = Vec3;

// Vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(const double t, const Vec3& v)
{
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vec3 operator*(const Vec3& v, const double t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3& v, const double t)
{
    return (1 / t) * v;
}

inline double dot(const Vec3& u, const Vec3& v)
{
    return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}

inline static Vec3 random_vector() {
    return Vec3(randomDouble(), randomDouble(), randomDouble());
}

inline static Vec3 random_vector(double min, double max){
    return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

Vec3 random_in_unitsphere() {

    while (true){

        Vec3 p = random_vector(-1.0, 1.0);
        if (p.squared_length() >= 1) continue;
        return p;

    }
}

inline static Vec3 random_unit_vector() {
    return unit_vector(random_in_unitsphere());
}

Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.squared_length() >= 1) continue;
        return p;
    }
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -std::sqrt(fabs(1.0 - r_out_perp.squared_length())) * n;
    return r_out_perp + r_out_parallel;
}

#endif