#pragma once
#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include "rt_project.h"
#include "color.h"

double camera_origin_x = 0.0;
double camera_origin_y = 0.0;
double camera_origin_z = 0.0;

double delta = 0.05;
double rotateByDegrees = 1;
double rotateByRadians = degrees_to_rad(rotateByDegrees);

struct OriginalCamera {

	bool hasChanged = false;

	double x;
	double y;
	double z;
	double focal_length = 1.0;

	Point3 origin = Point3(x, y, z);
};

struct OriginalCorner {
	Vec3 ogTopLeft;
};

class Camera {
public:
	Camera(const Point3& orig = Point3(0, 0, 0))
		: origin(orig){

		auto focal_length = 1.0;

		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * aspect_ratio;

		setOgTopLeft(focal_length);

		//double origin_x = 0.0;
		//double origin_y = 0.0;
		//double origin_z = 0.0;

		//origin = Point3(origin_x, origin_y, origin_z);
		//origin = orig;
		vertical = Vec3(0, viewport_height, 0);
		horizontal = Vec3(viewport_width, 0, 0);
		top_left_corner = origin - horizontal / 2 + vertical / 2 - Vec3(0.0, 0.0, focal_length);
		og_top_left = top_left_corner;
	}

	void setOgTopLeft(double focal_length) {
		og_top_left = origin - horizontal / 2 + vertical / 2 - Vec3(0.0, 0.0, focal_length);
	}

	void returnToOgTopLeft() {
		top_left_corner = og_top_left;
	}

	//void SomeCamera(const bool myCam, const Point3& orig = Point3(0, 0, 0)) : origin(orig) {
	//	auto aspect_ratio = global_aspect_ratio;
	//	auto width = global_width;
	//	auto height = global_height;
	//	auto focal_length = 1.0;

	//	auto viewport_height = 2.0;
	//	auto viewport_width = viewport_height * aspect_ratio;

	//	Vec3 tail = origin - Vec3(0, -1, 0);
	//	Vec3 head = origin;
	//	Vec3 direction = head - tail;
	//	Vec3 unitDir = unit_vector(direction);

	//}

	// Camera Rotation Functions

	inline void RotateUpDown(const bool positive) {
		// y = y cos(theta) - z sin(theta)
		// z = y sin(theta) + z cos(theta)
		auto x = top_left_corner.x();
		auto y = top_left_corner.y();
		auto z = top_left_corner.z();

		int s = positive ? 1 : -1;
		top_left_corner.e[1] = top_left_corner.e[1] * cos(s * rotateByRadians) - top_left_corner.e[2] * sin(s * rotateByRadians);
		top_left_corner.e[2] = top_left_corner.e[1] * sin(s * rotateByRadians) + top_left_corner.e[2] * cos(s * rotateByRadians);
		//return Vec3(camera_origin_x, camera_origin_y, camera_origin_z);
	}

	inline void RotateLeftRight(const bool positive) {
		// x = x cos(theta) + z sin(theta)
		// z = -x sin (theta) + z cos(theta)

		auto x = top_left_corner.x();
		auto y = top_left_corner.y();
		auto z = top_left_corner.z();

		int s = positive ? 1 : -1;
		top_left_corner.e[0] = top_left_corner.e[0] * cos(s * rotateByRadians) + top_left_corner.e[2] * sin(s * rotateByRadians);
		top_left_corner.e[2] = -top_left_corner.e[0] * sin(s * rotateByRadians) + top_left_corner.e[2] * cos(s * rotateByRadians);
		//return Vec3(camera_origin_x, camera_origin_y, camera_origin_z);
	}

	// Try using returns by values and references;
	inline void RotateLeftRight(const bool positive, Vec3& r) {

		int s = positive ? 1 : -1;
		r.e[0] = r.e[0] * cos(s * rotateByRadians) + r.e[2] * sin(s * rotateByRadians);
		r.e[2] = -r.e[0] * sin(s * rotateByRadians) + r.e[2] * cos(s * rotateByRadians);

	}

	/*Ray getRay(double u, double v) {
		return Ray(origin, top_left_corner + u * horizontal - v * vertical - origin);
	}*/

	Ray getRay(double u, double v) {
		return Ray(origin, top_left_corner + u * horizontal - v * vertical - origin);
	}

public:
	Point3 origin;
	Point3 top_left_corner;

private:
	Vec3 vertical;
	Vec3 horizontal;
	Point3 og_top_left;
	Vec3 direction;
	double fov;
	double aspect_ratio;
};


OriginalCamera ogCam = { false, 0.0, 0.0, 0.0, 1.0, Point3(0, 0, 0) };


#endif