#pragma once
// HEADER ONLY
#include <array>

struct Vec2D
{
    Vec2D() = default;
    Vec2D(float x, float y)
        : x{x}, y{y} {}
    float x, y;
};

struct Triangle{
    Triangle(const Vec2D& v1, const Vec2D& v2, const Vec2D& v3)
        : points{v1, v2, v3} {}
    std::array<Vec2D, 3> points;
};