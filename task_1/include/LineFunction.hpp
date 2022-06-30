#pragma once
// HEADER ONLY
#include "TaskStructs.hpp"
#include <algorithm>


struct LineFunction{
    LineFunction() = default;
    LineFunction(const Vec2D& begin, const Vec2D& end)
        : m_begin{begin}, m_end{end}, a{(end.y-begin.y)/(end.x-begin.x)}{
            b = begin.y - a*begin.x;
        }
    float operator()(float x) const { return a*x + b; }
    bool crossSection(const LineFunction& other){
        if(a == other.a)
            return false;
        float x = (other.b-b)/(a - other.a);
        if(x >= std::max(m_begin.x, other.m_begin.x) && x <= std::min(m_end.x, other.m_end.x)){
            return true;
        }
        return false;
    }
    float a;
    float b;
private:
    Vec2D m_begin;
    Vec2D m_end;
};