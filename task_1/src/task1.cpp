#include <iostream>
#include <iomanip>
#include "Colliding.hpp"


int main(){
    Triangle t1{Vec2D(0.3f, 3.f), Vec2D(1.4f, 0.3f), Vec2D(2.7f, 3.f)}; // red
    Triangle t2{Vec2D(1.4f, 1.6f), Vec2D(3.5f, 3.2f), Vec2D(3.f, 1.6f)}; // black
    Triangle t3{Vec2D(3.6f, 1.7f), Vec2D(2.7f, 4.3f), Vec2D(0.9f, 2.1f)}; // purple
    Triangle t4{Vec2D(3.7f, 5.3f), Vec2D(5.8f, 5.2f), Vec2D(4.6f, 1.2f)}; // blue
    Triangle t5{Vec2D(4.3f, 5.f), Vec2D(5.2f, 4.9f), Vec2D(4.7f, 2.6f)}; // green

    std::cout << std::boolalpha;
    std::cout << "Black and Purple: Expected = " << true << "\tFunction = " <<  isColliding(t2, t3) << std::endl;
    std::cout << "Blue and Green: Expected = " << true << "\tFunction = " <<  isColliding(t5, t4) << std::endl;
    std::cout << "Blue and Red: Expected = " << false << "\tFunction = " <<  isColliding(t1, t4) << std::endl;
    std::cout << "Red and Black: Expected = " << true << "\tFunction = " <<  isColliding(t1, t2) << std::endl;
    return 0;
}