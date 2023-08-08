#include <iostream>
#include <fstream>
#include <GL/glut.h>

#include <thread>
#include <functional>
#include <omp.h>
//#include <Eigen/Dense>

#include "rt_project.h"
#include "camera.h"
#include "color.h"
#include "ray.h"

#include "hittable_list.h"
#include "sphere.h"
//#include "test.h"

Color ColorRayGradient(const Ray& r)
{
    Vec3 unit_direction = unit_vector(r.direction());

    // Unit Direction in y axis can range from -1 to +1
    // Hence it is normalized to minimum value of 0 by adding 1.0
    // Now, since the maximum value can be (1.0 + 1.0) = 2.0, we multiply it with 0.5
    // This effectively clamps the value between 0 and 1

    auto t = 0.5 * (unit_direction.y() + 1.0);
    double maybegreen = 0;

    // if (unit_direction.y() > 0)
    // {
    //     maybegreen = 0;
    // }
    // else
    // {
    //     maybegreen = 0.5;
    // }

    // When Starting from Top Left, t is maximum (y axis is maxed),
    // therefore the second colour takes dominance first
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0) + Color(0, maybegreen, 0);
}

double hit_sphere(const Ray& ray, const double radius, const Point3& center)
{

    Vec3 oc = ray.origin() - center;
    Vec3 dir = ray.direction();

    auto a = dot(dir, dir);
    auto b = 2.0 * dot(dir, oc);
    auto c = dot(oc, oc) - radius * radius;

    auto D = b * b - 4 * a * c;

    if (D <= 0)
    {
        return -1;
    }
    else
    {
        auto root = std::sqrt(D);
        return (-b - root) / (2 * a);
    }
}

//////////////////////////////////
double hit_sphere_simplified(); //
//////////////////////////////////

Color ColorRaySphere(const Ray& r)
{

    if (hit_sphere(r, 0.5, Point3(0.0, 0.0, -1)) > 0)
    {
        return Color(1, 0, 0);
    }
    return ColorRayGradient(r);
}

Color MakeGround(const Ray& r);
Color BlackAndWhiteFromNormal(const Vec3& normal);


Color ColorRaySphereNormals(const Ray& r)
{

    Point3 center = Point3(0, 0, -1);

    auto t = hit_sphere(r, 0.5, center);

    if (t > 0.0)
    {
        Vec3 normal = unit_vector(r.t_length_in_dir(t) - center);
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
        //return BlackAndWhiteFromNormal(normal);
    }
    return MakeGround(r);
}

Color MakeGround(const Ray& r) {

    Point3 center = Point3(0, -100.5, -1);

    auto t = hit_sphere(r, 100, center);

    if (t > 0.0)
    {
        Vec3 normal = unit_vector(r.t_length_in_dir(t) - center);
        //return BlackAndWhiteFromNormal(normal);
        return Color(0, 1.0, 0);
    }
    return ColorRayGradient(r);

}

Color BlackAndWhiteFromNormal(const Vec3 &normal){

    double normal_sum = (normal.x() + normal.y() + normal.z()) / 3;
    Color black_and_white = Color(normal_sum + 1, normal_sum + 1, normal_sum + 1);
    return 0.5 * black_and_white;
}

Color RayColorWorld(const Ray& r, const Hittable& world, int depth) {

    if (depth <= 0){
        return Color(0, 0, 0);
    }
    hit_record rec;

    //if (world.hit(r, 0.001, infinity, rec)) {
    //    Point3 new_ray = rec.p + rec.normal + random_in_unitsphere();
    //    //return 0.5 * (rec.normal + Color(1,1,1));
    //    return 0.5 * ( RayColorWorld( Ray(rec.p, new_ray - rec.p), world , depth-1) );
    //}

    if (world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.material_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * RayColorWorld(scattered, world, depth - 1);
        return Color(0, 0, 0);
    }


    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

/////////////////////////////////////////////////////////////////////////
// Keyboard input Function
/////////////////////////////////////////////////////////////////////////


// origin, lookfrom, lookat, up, fov, aperture, focal_dist, aspect_ratio
// 

// Random World
auto lookfrom = Point3(13,2,3);
auto lookat = Point3(0, 0, 0);

// Sphere Hex
//auto lookfrom = Point3(0, 10-2*sqrt(3), 10);
//auto lookat = Point3(0, 10 - 2 * sqrt(3), 0);

// 3 Sphere
//auto lookfrom = Point3(-2, 2, 1);
//auto lookat = Point3(0, 0, -1);

// Glass on glass
//auto lookfrom = Point3(5, 3, 0);
//auto lookat = Point3(0, 0, 0);

// Metal in glass
//auto lookfrom = Point3(0, 5, 6);
//auto lookat = Point3(0, 5, 0);



auto up = Point3(0, 1, 0);
auto aperture = 0.2;
auto dist_to_focus = (lookfrom-lookat).length();
Camera cam = Camera(lookfrom, lookfrom, lookat, up, 20.0, aperture, dist_to_focus);
//Camera cam = Camera(lookfrom, lookfrom, lookat, up, 20, aperture, dist_to_focus);


void buttons(unsigned char key, int x, int y) {

    // Movements
    if (key == 'w') {
        cam.origin.e[2] -= delta;
        cam.top_left_corner.e[2] -= delta;
    }
    if (key == 's') {
        cam.origin.e[2] += delta;
        cam.top_left_corner.e[2] += delta;
    }
    if (key == 'a') {
        cam.origin.e[0] -= delta;
        cam.top_left_corner.e[0] -= delta;
    }

    if (key == 'd') {
        cam.origin.e[0] += delta;
        cam.top_left_corner.e[0] += delta;
    }

    if (key == 'o'){
        cam.fov -= 0.1;
    }
    if (key == 'p'){
        cam.fov += 0.1;
    }

    // Camera angle
    if (key == 'i') cam.RotateUpDownFocus(true);
    if (key == 'k') cam.RotateUpDownFocus(false);
    if (key == 'j') cam.RotateLeftRight(true);
    if (key == 'l') cam.RotateLeftRight(false);


    if (key == 'r') {
        cam.origin.e[0] = ogCam.x;
        cam.origin.e[1] = ogCam.y;
        cam.origin.e[2] = ogCam.z;
        cam.returnToOgTopLeft();
    }

    if (key == 't') cam.returnToOgTopLeft();
    glutPostRedisplay();
}

void specialButtons(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        cam.origin.e[1] += delta;
        cam.top_left_corner.e[1] += delta;
    }
    if (key == GLUT_KEY_DOWN) {
        cam.origin.e[1] -= delta;
        cam.top_left_corner.e[1] -= delta;
    }
    glutPostRedisplay();
}

void display()
{

    std::ofstream img("testing/FR_1080p_100SPP.ppm");

    // Viewport bits
    // Adjusting the image dimensions-

    const auto aspect_ratio = global_aspect_ratio;
    const int img_width = global_width;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int depth = 50;

    // Create the World-
    HittableList world;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Metal>(Color(0.7, 0.3, 0.3), 0.5);
    auto material_left = make_shared<Dielectric>(1.5);
    auto material_right = make_shared<Metal>(Color(0.3, 0.7, 0.5));

    world.add(make_shared<Sphere>(Point3(0, -101, -1), 100.5, material_ground));
    world.add(make_shared<Sphere>(Point3(0, 0, -1.0), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.05, 0, -1), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(-1.05, 0, -1), -0.4, material_left));
    world.add(make_shared<Sphere>(Point3(1, 0, -1), 0.5, material_right));

    HittableList random_world = random_scene();
    HittableList glass_glass = glass_on_glass();
    HittableList hex_pattern = metal_hexagon();
    HittableList metal_in_gls = metal_in_glass();

    /*world.add(make_shared<Sphere>(Point3(-1.0, 0, -1.0), 0.5));
    world.add(make_shared<Sphere>(Point3(1.0, 0, -1.0), 0.5));*/

    //world.add(make_shared<Sphere>(Point3(0.4, 0.5, -1), 0.25, material_left));
    //world.add(make_shared<Sphere>(Point3(-0.4, 0.5, -1), 0.25, material_right));
    //world.add(make_shared<Sphere>(Point3(0, 0, -0.5), 0.1, material_center));

    /////////////////////////
    // Creating the Camera //
    /////////////////////////

    //auto viewport_height = 2.0;
    //auto viewport_width = aspect_ratio * viewport_height;
    //auto focal_length = 1;

    //auto origin = Point3(0.0, 0.0, 0.0);
    //auto horizontal = Vec3(viewport_width, 0.0, 0.0);
    //auto vertical = Vec3(0.0, viewport_height, 0.0);

    //auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);
    //auto lower_right_corner = origin + horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);
    //auto top_left_corner = origin - horizontal / 2 + vertical / 2 - Vec3(0.0, 0.0, focal_length);

    //auto center = origin - Vec3(0.0, 0.0, focal_length);

    //Vec3 test_unit = unit_vector(lower_left_corner);


    ///////////////////////////////////////
    //Camera cam = Camera(Point3(camera_origin_x, camera_origin_y, camera_origin_z));
    ///////////////////////////////////////


    //////// Rendering ///////////////////////////////////////////////////////////////

    //RenderInitFile(img, img_width, img_height, 255);

    // Here's an array to store all the pixel values temporarily-
    Color** results = new Color*[img_height];
    for (int i = 0; i < img_height; ++i) {
        results[i] = new Color[img_width];
    }
    //std::vector<std::vector<Color>> results(img_height, std::vector<Color>(img_width, Color(0,0,0)));
    int scanlines = 0;

    #pragma omp parallel for
    for (int j = 0; j < img_height; j++)
    //for (int j = img_height - 1; j >= 0; j--)
    {
        std::cerr << "Scanlines Processed : " << ++scanlines <<"/" << img_height << "\t\t";
        std::cerr << "Processing Scanline - " << img_height - j << "\n";

        for (int i = 0; i < img_width; i++)
        {

            Color pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; s++) 
            {
                auto u = (i + randomDouble()) / (img_width + 1);
                auto v = (j + randomDouble()) / (img_height + 1);
                Ray r = cam.getRay(u, v);
                pixel_color += RayColorWorld(r, random_world, depth);
            }
            //#pragma omp critical
            results[j][i] = pixel_color;

            //DisplayColorGlutAntiAliased(pixel_color, i, img_height - j, samples_per_pixel);
            //glFlush();

            //std::cerr << "u: ";
            //ShowRawValues(std::cerr, cam.u);
            //std::cerr << "v: ";
            //ShowRawValues(std::cerr, cam.v);


            //WriteColorToFileAntiAliased(img, pixel_color, samples_per_pixel);
            
            //Color pixel_color = ColorRaySphereNormals(r);
            //Color pixel_color = RayColorWorld(r, world);
            // Color all_white = Color(1.0, 1.0, 1.0);
            //DisplayColorGlut(pixel_color, i, img_height - j);


        }
    }
    for (int j = 0; j < img_height; j++) {
        std::cerr << "Printing Scanline : " << img_height - j << "\n";
        for (int i = 0; i < img_width; i++) {
            DisplayColorGlutAntiAliased(results[j][i], i, img_height - j, samples_per_pixel);
            //glFlush();
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

    //std::thread t(std::bind(mainLoop, img, samples_per_pixel, cam, world, depth));

    ///////////////////////////////////////////////////////////////////////////

    // std::cout<<"Ray at top left corner = "<<ShowRawValues(std::cout, )
    //std::cerr << "Done";

}

int main(int argc, char** argv)
{

    int width = global_width;
    int height = global_height;

    std::cerr << "Window : " << width << height;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Output");
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons);
    glutSpecialFunc(specialButtons);
    glutMainLoop();
    return 0;

}