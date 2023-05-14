#pragma once

#ifndef TEST_H
#define TEST_H

#include "rt_project.h"
#include"color.h"
#include"camera.h"
#include"GL/glut.h"

Color RayColorWorld(const Ray& r, const Hittable& world, int depth) {

    if (depth <= 0) {
        return Color(0, 0, 0);
    }
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        Point3 new_ray = rec.p + rec.normal + random_in_unitsphere();
        //return 0.5 * (rec.normal + Color(1,1,1));
        return 0.5 * (RayColorWorld(Ray(rec.p, new_ray - rec.p), world, depth - 1));
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


void mainLoop(std::ofstream img, int samples_per_pixel, Camera &cam, HittableList &world, int depth) {

    int img_height = global_height;
    int img_width = global_width;

    RenderInitFile(img, img_width, img_height, 255);
    for (int j = 0; j < img_height; j++)
        //for (int j = img_height - 1; j >= 0; j--)
    {
        std::cerr << "Scanlines Remaining : " << img_height - j << "\n";

        for (int i = 0; i < img_width; i++)
        {

            Color pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; s++)
            {
                auto u = (i + randomDouble()) / (img_width + 1);
                auto v = (j + randomDouble()) / (img_height + 1);
                Ray r = cam.getRay(u, v);
                pixel_color += RayColorWorld(r, world, depth);
            }

            DisplayColorGlutAntiAliased(pixel_color, i, img_height - j, samples_per_pixel);
            glFlush();

        }
    }
    glFlush();
    std::cout << "\n\nOrigin : \n";
    ShowRawValues(std::cerr, cam.origin);
    std::cout << "Top Left Corner : \n";
    ShowRawValues(std::cerr, cam.top_left_corner);
    std::cout << "Focus : \n";
    ShowRawValues(std::cerr, cam.focal_length_vector);
    std::cout << "Fov : " << cam.fov;

}

#endif