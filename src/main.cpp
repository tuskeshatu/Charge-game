#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shapes");

    // Create the circles
    sf::CircleShape circle1(50);
    circle1.setFillColor(sf::Color::Red);
    circle1.setPosition(100, 200);

    sf::CircleShape circle2(50);
    circle2.setFillColor(sf::Color::Blue);
    circle2.setPosition(400, 200);

    // Create the rounded rectangle
    sf::RectangleShape rectangle(sf::Vector2f(300, 100));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(2.f);
    rectangle.setPosition(200, 250);
    rectangle.setSize(sf::Vector2f(50,50));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle1);
        window.draw(circle2);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}