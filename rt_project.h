#pragma once

#ifndef RT_PROJECT_H
#define RT_PROJECT_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const int global_width = 400;
const auto global_aspect_ratio = 16.0/9.0;
const auto global_height = static_cast<int>(global_width / global_aspect_ratio);

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_rad(double degree) {
	//pi = 180 degrees
	//1 degree = pi/180
	//n degrees = pi*n/180
	return pi * degree / 180.0;
}

inline double randomDouble() {
	return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
	return min + randomDouble()*(max - min);
}

inline double clamp(double v, double min, double max) {
	return v < min ? min : (v > max ? max : v);
}

#include "ray.h"
#include "3dvector.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "random_world.h"
#include "color.h"

#endif
