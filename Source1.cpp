#include <iostream>
#include <fstream>
#include <GL/glut.h>

#include "color.h"
#include "ray.h"

// int main()
// {
//     std::ofstream img("testingFunctions.ppm");

//     const int img_width = 256;
//     const int img_height = 256;

//     std::cout << "P3\n";
//     img << "P3\n";
//     std::cout << img_width << " " << img_height << "\n255\n";
//     img << img_width << " " << img_height << "\n255\n";

//     for (int j = 0; j < img_height; j++)
//     {
//         std::cerr << "Scanlines Remaining : " << img_height - j << "\n";
//         for (int i = 0; i < img_width; i++)
//         {

//             auto r = double(i) / img_width;
//             auto g = double(j) / img_height;
//             auto b = 0.25;

//             auto ir = static_cast<int>(255.999 * r);
//             auto ig = static_cast<int>(255.999 * g);
//             auto ib = static_cast<int>(255.999 * b);

//             // std::cout << ir << " " << ig << " " << ib << "\n";
//             img << ir << " " << ig << " " << ib << "\n";
//         }
//     }

//     // for (int j = img_height - 1; j >= 0; --j)
//     // {
//     //     for (int i = 0; i < img_width; ++i)cls
//     //     {
//     //         auto r = double(i) / (img_width - 1);
//     //         auto g = double(j) / (img_height - 1);
//     //         auto b = 0.25;

//     //         int ir = static_cast<int>(255.999 * r);
//     //         int ig = static_cast<int>(255.999 * g);
//     //         int ib = static_cast<int>(255.999 * b);

//     //         // std::cout << ir << ' ' << ig << ' ' << ib << '\n';
//     //         img << ir << ' ' << ig << ' ' << ib << '\n';
//     //     }
//     // }

//     std::cout << "done";
// }

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

Color ColorRaySphereNormals(const Ray& r)
{

    Point3 center = Point3(0, 0, -1);

    auto t = hit_sphere(r, 0.5, center);

    if (t > 0.0)
    {
        Vec3 normal = unit_vector(r.t_length_in_dir(t) - center);
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }
    return ColorRayGradient(r);
}

void display()
{
    // const int img_height = 256;
    // const int img_width = 256;

    // std::ofstream img("testingFunctions3.ppm");

    // std::cout << "P3\n";
    // img << "P3\n";
    // std::cout << img_width << " " << img_height << "\n255\n";
    // img << img_width << " " << img_height << "\n255\n";

    // for (int j = 0; j < img_height; j++)
    // {
    //     std::cerr << "Scanlines Remaining : " << img_height - j << "\n";

    //     for (int i = 0; i < img_width; i++)
    //     {
    //         auto r = double(i) / img_width;
    //         auto g = double(j) / img_height;
    //         auto b = 0.25;

    //         // auto ir = static_cast<int>(255.999 * r);
    //         // auto ig = static_cast<int>(255.999 * g);
    //         // auto ib = static_cast<int>(255.999 * b);

    //         Color pixel_color(r, g, b);

    //         WriteColorToFile(img, pixel_color);
    //     }
    // }

    // Viewport bits

    // Adjusting the image dimensions-

    std::ofstream img("testing/spherenormalbanvadobhagwan.ppm");

    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);

    /////////////////////////
    // Creating the Camera //
    /////////////////////////

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1;

    auto origin = Point3(0.0, 0.0, 0.0);
    auto horizontal = Vec3(viewport_width, 0.0, 0.0);
    auto vertical = Vec3(0.0, viewport_height, 0.0);

    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);
    auto lower_right_corner = origin + horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focal_length);
    auto top_left_corner = origin - horizontal / 2 + vertical / 2 - Vec3(0.0, 0.0, focal_length);

    auto center = origin - Vec3(0.0, 0.0, focal_length);

    // WriteColour(std::cout, lower_left_corner);
    // ShowRawValues(std::cout, lower_left_corner);
    Vec3 test_unit = unit_vector(lower_left_corner);

    // std::cout << "Unit Vector:\n";
    // ShowRawValues(std::cout, test_unit);

    //////// Rendering ////////

    RenderInitFile(img, img_width, img_height, 255);

    for (int j = 0; j < img_height; j++)
        // for (int j = img_height - 1; j >= 0; j--)
    {
        std::cerr << "Scanlines Remaining : " << img_height - j << "\n";

        for (int i = 0; i < img_width; i++)
        {
            auto u = double(i) / img_width;
            auto v = double(j) / img_height;

            Ray r(origin, top_left_corner + u * horizontal - v * vertical - origin);
            // if (((i == 0) && (j == 0)) || ((i == 0) && (j == img_height - 1)) || ((i == img_width - 1) && (j == 0)) || ((i == img_width - 1) && (j == img_height - 1)))
            // {
            //     std::cout << "Point-\n";
            //     ShowRawValues(std::cout, r.direction());

            //     std::cout << "Colours-\n";

            //     std::cout << "Raw Colour-\n";
            //     Color pixel_color = ColorRayGradient(r);
            //     ShowRawValues(std::cout, pixel_color);

            //     std::cout << "Actual Colour written-\n";
            //     WriteColour(std::cout, pixel_color);
            //     // WriteColorToFile(img, pixel_color);

            //     std::cout << "\n";

            //     // continue;
            // }
            // WriteColour(std::cout, r.direction());
            Color pixel_color = ColorRaySphereNormals(r);
            // Color all_white = Color(1.0, 1.0, 1.0);
            DisplayColorGlut(pixel_color, i,j);
        }
    }
    glFlush();

    // std::cout<<"Ray at top left corner = "<<ShowRawValues(std::cout, )
    std::cerr << "Done";
}

int main(int argc, char** argv)
{
    int width = 640;
    int height = 400;
    glutInit(&argc, argv);   // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode
    glutInitWindowSize(width, height);   // Set window size
    glutInitWindowPosition(100, 100);   // Set window position
    glutCreateWindow("Lab Evaluation 1");   // Create window
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   // Set background color
    glViewport(0, 0, 400, 225);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 225);
    glutDisplayFunc(display);   // Set the display callback function
    glutMainLoop();   // Enter the GLUT event processing loop
    return 0;

}