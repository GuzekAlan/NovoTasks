#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "LineFunction.hpp"
#include "utils.hpp"
#include <cmath>

int main(){

    // Parameters
    size_t window_width = 800;
    size_t window_height = 400;

    float circ_radius = 125.f;
    auto circ_pos = sf::Vector2f(window_width/2.f-circ_radius, window_height/2.f-circ_radius);

    auto rect_size = sf::Vector2f(200, 100);
    auto rect_pos = circ_pos + rect_size + sf::Vector2f(30, -100);

    auto color_c_bad = sf::Color::Red;
    auto color_c_good = sf::Color::Green;
    auto color_r_bad = sf::Color(200, 160, 180, 230);
    auto color_r_good = sf::Color(100, 220, 120, 230);

    float rotate_speed = 4/360.f;
    int rotate_angle = 0;
//    auto rotate_radius = sqrt(pow(rect_size.x, 2) + pow(rect_size.y, 2)) / 2;

    // Setting Objects
    auto  window = sf::RenderWindow(sf::VideoMode(window_width, window_height),
                                    "Task 2",
                                    sf::Style::Titlebar | sf::Style::Close);

    auto rectangle = sf::RectangleShape();
    rectangle.setSize(rect_size);
    rectangle.setFillColor(color_r_bad);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setPosition(rect_pos);

    auto circle = sf::CircleShape();
    circle.setRadius(circ_radius);
    circle.setFillColor(color_c_bad);
    circle.setOutlineColor(sf::Color::Black);
    circle.setPosition(circ_pos);

    auto clock = sf::Clock();

    int delta_rotate = 0;

    // Main Loop
    while(window.isOpen()){
        window.clear(sf::Color::White);

        // Event Loop
        auto event = sf::Event();
        while(window.pollEvent(event)){
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:     // TODO: Check intersection only on keypressed
                    switch(event.key.code) {
                        case sf::Keyboard::Key::Left:
                        case sf::Keyboard::Key::Q:
                            delta_rotate = -1;
                            break;
                        case sf::Keyboard::Key::Right:
                        case sf::Keyboard::Key::E:
                            delta_rotate = 1;
                            break;
                        case sf::Keyboard::Key::Escape:
                            window.close();
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Key::Right:
                        case sf::Keyboard::Key::E:
                        case sf::Keyboard::Key::Left:
                        case sf::Keyboard::Key::Q:
                            delta_rotate = 0;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }


        if(clock.getElapsedTime().asSeconds() >= rotate_speed ){
            rotate_angle = (rotate_angle + delta_rotate)%360;
            if(intersectCircleRect(rectangle, circle, rotate_angle)){
                rectangle.setFillColor(color_r_good);
                circle.setFillColor(color_c_good);
            }
            else{
                rectangle.setFillColor(color_r_bad);
                circle.setFillColor(color_c_bad);
            }
            clock.restart();
        }


        window.draw(circle);
        window.draw(rectangle, getCenterRotationMatrix(rotate_angle, rectangle));
        window.display();
    }

    return 0;
}