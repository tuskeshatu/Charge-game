#include <SFML\Graphics.hpp>
#include <memory>

#include "obstacle.h"
#include "settings.h"

extern const char debug;
extern sf::RenderWindow window;

// Constructor
Obstacle::Obstacle(const float radius, const double charge, const sf::Vector2f &pos)
    : Charge(charge), collisionBox(radius), body(std::make_shared<sf::CircleShape>(radius * 4.0f))
{
    // Load textures
    static sf::Texture repulseTexture;
    static sf::Texture attractTexture;

    // Load textures
    if (!repulseTexture.loadFromFile("textures/repulse_obstacle_texture.png"))
        throw std::runtime_error("Obstacle: Could not load repulse texture");
    if (!attractTexture.loadFromFile("textures/attract_obstacle_texture.png"))
        throw std::runtime_error("Obstacle: Could not load attract texture");

    // Set texture
    body->setFillColor(sf::Color::White);

    body->setTexture(charge > 0 ? &repulseTexture : &attractTexture);

    // Set origin and position
    body->setOrigin(radius * 4.0f, radius * 4.0f);
    body->setPosition(pos);
}

// Set position, guard against placing outside of window
void Obstacle::setPosition(sf::Vector2f &newPos)
{
    // Clip coordinates to extremeties of the window
    if (newPos.x < 0)
        newPos.x = 0;
    else if (newPos.x > window.getSize().x)
        newPos.x = window.getSize().x;
    if (newPos.y < 0)
        newPos.y = 0;
    else if (newPos.y > window.getSize().y)
        newPos.y = window.getSize().y;

    body->setPosition(newPos);
}