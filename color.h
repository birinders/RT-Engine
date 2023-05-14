#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "3dvector.h"
#include "rt_project.h"
#include <iostream>

void ShowRawValues(std::ostream& out, const Vec3& v)
{
    out << "x: " << v.x() << " y: " << v.y() << " z: " << v.z() << "\n";
}

void WriteColour(std::ostream& out, Color pixel_color)
{
    out << static_cast<int>(255.999 * pixel_color.x()) << " "
        << static_cast<int>(255.999 * pixel_color.y()) << " "
        << static_cast<int>(255.999 * pixel_color.z()) << "\n";
}

void WriteColorToFile(std::ofstream& file, Color pixel_color)
{
    file << static_cast<int>(255.999 * pixel_color.x()) << " "
        << static_cast<int>(255.999 * pixel_color.y()) << " "
        << static_cast<int>(255.999 * pixel_color.z()) << "\n";
}

void WriteColorToFileAntiAliased(std::ofstream& file, Color pixel_color, int samples) {

    double scale = 1.0 / samples;

    double r = sqrt(pixel_color.x() * scale);
    double g = sqrt(pixel_color.y() * scale);
    double b = sqrt(pixel_color.z() * scale);

    file << static_cast<int>(256 * clamp(r, 0, 0.9999)) << " "
        << static_cast<int>(256 * clamp(g, 0, 0.9999)) << " "
        << static_cast<int>(256 * clamp(b, 0, 0.9999)) << "\n";

}

void DisplayColorGlut(Color pixel_color, int i, int j) {

    glColor3f(pixel_color.x(), pixel_color.y(), pixel_color.z());
    glBegin(GL_POINTS);
    glVertex2i(i, j);
    glEnd();
}

void DisplayColorGlutAntiAliased(Color pixel_color, int i, int j, int samples) {
    
    double scale = 1.0 / samples;

    double r = sqrt(pixel_color.x() * scale);
    double g = sqrt(pixel_color.y() * scale);
    double b = sqrt(pixel_color.z() * scale);

    glColor3f(clamp(r,0,0.999999), clamp(g, 0, 0.999999), clamp(b, 0, 0.999999));
    glBegin(GL_POINTS);
    glVertex2i(i, j);
    glEnd();
}

void RenderInitPrint(std::ostream& out, int image_width, int image_height, int max_colors)
{
    out << "P3\n"
        << image_width << " " << image_height << "\n255\n";
}

void RenderInitFile(std::ofstream& file, int image_width, int image_height, int max_colors)
{
    file << "P3\n"
        << image_width << " " << image_height << "\n255\n";
}

Color randomColor() {
    return Color(randomDouble(), randomDouble(), randomDouble());
}

Color randomColor(double min, double max) {
    return Color(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

#endif