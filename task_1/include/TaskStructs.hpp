#pragma once
// HEADER ONLY
#include <array>

struct Vec2D
{
    Vec2D() = default;
    Vec2D(float x, float y)
        : x{x}, y{y} {}
    float x, y;
    Vec2D operator-(const Vec2D& other) { return Vec2D(x-other.x, y-other.y); }
    Vec2D operator+(const Vec2D& other) { return Vec2D(x+other.x, y+other.y); }
    Vec2D operator*(float a) { return Vec2D(x*a, y*a); }
};

struct Triangle{
    Triangle(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3)
        : points{v1, v2, v3} {}
    std::array<Vec2D, 3> points;
};