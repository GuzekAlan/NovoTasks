#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

int main(){

    // Parameters
    auto window_width = 800;
    auto window_height = 400;

    auto circ_radius = 125.f;
    auto circ_pos = sf::Vector2f(window_width/2.f-circ_radius, window_height/2.f-circ_radius);

    auto rect_size = sf::Vector2f(200, 100);
    auto rect_pos = circ_pos + rect_size;

    auto color_c_bad = sf::Color::Red;
    auto color_c_good = sf::Color::Green;
    auto color_r_bad = sf::Color(200, 160, 180, 230);
    auto color_r_good = sf::Color(100, 220, 120, 230);

    auto rotate_speed = 6/360.f;
    auto rotate_angle = -1.f;


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

    // Main Loop
    while(window.isOpen()){
        window.clear(sf::Color::White);

        // Event Loop
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }


        if(clock.getElapsedTime().asSeconds() >= rotate_speed){
            rectangle.rotate(rotate_angle);
            rectangle.move(sf::Vector2f(
                    rectangle.getSize().x / 2 * cos(rectangle.getRotation()-rotate_angle),
                    rectangle.getSize().y / 2 * sin(rectangle.getRotation()-rotate_angle)
                    ));
            clock.restart();
        }


        window.draw(circle);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}