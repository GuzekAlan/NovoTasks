#pragma once
// HEADER ONLY
#include "TaskStructs.hpp"
#include "LineFunction.hpp"
#include <algorithm>


std::array<Vec2D, 3> getSortedPoints(const Triangle& triangle){
    std::array<Vec2D, 3> sortedPoints = triangle.points;
    std::sort(sortedPoints.begin(), sortedPoints.end(), [](const Vec2D& a, const Vec2D& b){
        return a.x < b.x;
    });
    return sortedPoints;
}

std::array<LineFunction, 3> getEdges(const std::array<Vec2D, 3>& sortedPoints){
    return {LineFunction(sortedPoints[0], sortedPoints[1]),
            LineFunction(sortedPoints[1], sortedPoints[2]),
            LineFunction(sortedPoints[0], sortedPoints[2])};
}

bool isPointBetweenFunctions(const Vec2D& point, 
    const std::array<LineFunction, 3>& edges,
    const std::array<Vec2D, 3>& sortedPoints){
    if(point.x >= sortedPoints[0].x){
        if(point.x > sortedPoints[2].x){
            return false;
        }
        else if(point.x <= sortedPoints[1].x){
            if(point.y >= edges[2](point.x)){
                if(point.y <= edges[0](point.x)) return true;
            }
            else{
                if(point.y >= edges[0](point.x)) return true;
            }
        }
        else{
            if(point.y >= edges[2](point.x)){
                if(point.y <= edges[1](point.x)) return true;
            }
            else{
                if(point.y >= edges[1](point.x)) return true;
            }
        }
    }
    return false;
}

bool isColliding(const Triangle& triangle1, const Triangle& triangle2){
    
    // Crossing Edges
    auto sortedPoints1 = getSortedPoints(triangle1);
    auto edges1 = getEdges(sortedPoints1);
    auto sortedPoints2 = getSortedPoints(triangle2);
    auto edges2 = getEdges(sortedPoints2);

    for(auto& e1: edges1){
        for(auto& e2: edges2){
            if(e1.crossSection(e2)){
                return true;
            }
        }
    }

    // T1 in T2
    for(auto& point : triangle1.points){
        if(isPointBetweenFunctions(point, edges2, sortedPoints2)){
            return true;
        }
    }

    // T2 in T1
    for(auto& point : triangle2.points){
        if(isPointBetweenFunctions(point, edges1, sortedPoints1)){
            return true;
        }
    }

    return false;
}