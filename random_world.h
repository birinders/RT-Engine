#pragma once
#ifndef RANDOM_WORLD_H
#define RANDOM_WORLD_H

#include "rt_project.h"
#include "color.h"


HittableList random_scene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = randomColor() * randomColor();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = randomColor(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}


HittableList glass_on_glass() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.6, 0.7));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(-1, 1, 0), 1.4, material1));

    auto material2 = make_shared<Dielectric>(2);
    world.add(make_shared<Sphere>(Point3(1.5, 1.5, 0), 1.3, material1));

    return world;

}
HittableList metal_hexagon() {

    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.7, 0.6, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    auto glass_sphere = make_shared<Dielectric>(1.8);
    //Top left right
    world.add(make_shared<Sphere>(Point3(-2, 10, 0), 2, glass_sphere));
    world.add(make_shared<Sphere>(Point3(-2, 10, 0), -1.8, glass_sphere));

    world.add(make_shared<Sphere>(Point3(2, 10, 0), 2, glass_sphere));
    world.add(make_shared<Sphere>(Point3(2, 10, 0), -1.8, glass_sphere));


    //Left right
    world.add(make_shared<Sphere>(Point3(-4, 10 - 2*sqrt(3), 0), 2, glass_sphere));
    world.add(make_shared<Sphere>(Point3(-4, 10 - 2 * sqrt(3), 0), -1.8, glass_sphere));

    world.add(make_shared<Sphere>(Point3(4, 10 - 2 * sqrt(3), 0), 2, glass_sphere));
    world.add(make_shared<Sphere>(Point3(4, 10 - 2 * sqrt(3), 0), -1.8, glass_sphere));


    //Bottom left right
    world.add(make_shared<Sphere>(Point3(-2, 10 - 4 * sqrt(3), 0), 2, glass_sphere));
    world.add(make_shared<Sphere>(Point3(-2, 10 - 4 * sqrt(3), 0), -1.8, glass_sphere));

    world.add(make_shared<Sphere>(Point3(2, 10 - 4 * sqrt(3), 0), 2, glass_sphere));
    world.add(make_shared<Sphere>(Point3(2, 10 - 4 * sqrt(3), 0), -1.8, glass_sphere));

    //Metal
    auto metal_sphere = make_shared<Metal>(Color(0.7, 0.8, 0.9));
    world.add(make_shared<Sphere>(Point3(0, 10 - 2 * sqrt(3), -6), 5, metal_sphere));


    return world;

}

HittableList metal_in_glass() {

    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.7, 0.9));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    auto glass_sphere = make_shared<Dielectric>(1);
    world.add(make_shared<Sphere>(Point3(0, 5, 0), 3, glass_sphere));
    //world.add(make_shared<Sphere>(Point3(0, 5, 0), -2.8, glass_sphere));

    auto metal_sphere = make_shared<Metal>(Color(1.0, 0.4, 0.4));
    world.add(make_shared<Sphere>(Point3(0, 6.5, 0), 1, metal_sphere));

    return world;

}

#endif