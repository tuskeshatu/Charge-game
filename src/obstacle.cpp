#include <SFML\Graphics.hpp>
#include <memory>
#include <iostream>

#include "obstacle.h"
#include "settings.h"
#include "player.h"
#include "obstacleAnimation.h"
#include "animation.h"

extern const char debug;
extern sf::RenderWindow window;
extern Player player;

// Constructor
Obstacle::Obstacle(const float radius, const double charge, const sf::Vector2f &pos)
    : Charge(charge), collisionBox(radius), body(std::make_shared<sf::CircleShape>(radius * 4.0f)), vectorToPlayer(pos - player.getBody()->getPosition()) , distanceSquaredToPlayer(vectorToPlayer.x * vectorToPlayer.x + vectorToPlayer.y * vectorToPlayer.y)
    , animation(charge < 0 ? Animation::Type::RepulseObstacle : Animation::Type::AttractObstacle)
{
    // Set texture
    body->setFillColor(sf::Color::White);

    body->setTexture(animation.getTexture());

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

// Update vector pointing from obstacle to player
void Obstacle::updateVectorToPlayer()
{
    vectorToPlayer = body->getPosition() - player.getBody()->getPosition();
    if (debug == 7)
        std::cout << "Obstacle:\tx: " << vectorToPlayer.x << "\ty: " << vectorToPlayer.y << "\t";
}

// Update distance to player
void Obstacle::updateDistanceSquaredToPlayer()
{
    // Calculate distance squared to player
    distanceSquaredToPlayer = vectorToPlayer.x * vectorToPlayer.x + vectorToPlayer.y * vectorToPlayer.y;
    
    // Guard against negative distance
    if (distanceSquaredToPlayer < 0)
        distanceSquaredToPlayer = 0;

    if (debug == 7)
        std::cout << "Distance to player: " << distanceSquaredToPlayer << std::endl;
}