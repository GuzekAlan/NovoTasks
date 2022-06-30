#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>


auto getCenterRotationMatrix(float angle, const sf::RectangleShape& rectangle) -> sf::Transform {
    auto dx = rectangle.getSize().x/2 + rectangle.getPosition().x;
    auto dy = rectangle.getSize().y/2 + rectangle.getPosition().y;
    return sf::Transform().translate(dx, dy).rotate(angle).translate(-dx, -dy); // Rotating in center of a rectangle
}

auto getVectorLength(const sf::Vector2f& vector) -> double {
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

auto getCircleCenter(const sf::CircleShape& circle) -> sf::Vector2f {
    return circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
}

auto isPointInCircle(const sf::Vector2f& point, const sf::CircleShape& circle) -> bool {
    return getVectorLength(point- getCircleCenter(circle)) <= circle.getRadius();
}

auto intersectCircleRect(const sf::RectangleShape& rectangle, const sf::CircleShape& circle,
                         int angle, bool approx = false) -> bool {
    auto Points = std::array<sf::Vector2f, 4>{rectangle.getPosition(),
                                              rectangle.getPosition(),
                                              rectangle.getPosition(),
                                              rectangle.getPosition()};
    Points[1].x += rectangle.getSize().x;;
    Points[2].x += rectangle.getSize().x;
    Points[2].y += rectangle.getSize().y;
    Points[3].y += rectangle.getSize().y;
    std::for_each(Points.begin(), Points.end(), [&angle, &rectangle](sf::Vector2f& point){
        point = getCenterRotationMatrix(angle, rectangle).transformPoint(point);
    });
    if(std::any_of(Points.begin(), Points.end(), [&circle](const sf::Vector2f& point){
        return isPointInCircle(point, circle);
    })){
        return true;
    }

    if(approx)
        return false;

    auto Lines = std::array<LineFunction<float>, 4>();
    for(int i = 0; i < 4; i++){
        Lines[i] = LineFunction(Points[i], Points[(i+1)%4]);
    }

    for(auto& line : Lines){
        std::cout << "a: " << line.m_a << "\t b: " << line.m_b << std::endl;
    }
    std::cout << "---" << std::endl;

    if (std::any_of(Lines.begin(), Lines.end(), [&circle](const LineFunction<float> &line) {
        try{
            auto intersection = line.intersectLines(line.getOrthogonal(getCircleCenter(circle)));
            if(line.isWithinBoundries(intersection)){
                std::cout << "X: " << intersection.x << "\tY: " << intersection.y << std::endl;
                std::cout << "distance: " << getVectorLength(intersection - getCircleCenter(circle)) << std::endl;
                return isPointInCircle(intersection, circle);

//            std::cout << "Circle: " << getCircleCenter(circle).x << "\t" << getCircleCenter(circle).y << std::endl;
            }

            return false;
        }catch(const std::invalid_argument& ex) {return false;}

    })) {
        return true;
    }


    return false;
}