#include <SFML\Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "charge.h"
#include "player.h"
#include "obstacleAnimation.h"
#include "obstacle.h"

extern Player player;
extern sf::RenderWindow window;

ObstacleAnimation::ObstacleAnimation(const Animation::Type type) : Animation(type)
{  
    texture = type == Animation::Type::RepulseObstacle ? repulseTexture : attractTexture;
}

void ObstacleAnimation::applyTransform(Charge &toTransform) const
{
    if (typeid(toTransform) != typeid(Obstacle))
        throw std::invalid_argument("toTransform must be of type Obstacle");

    Obstacle &obstacle = dynamic_cast<Obstacle &>(toTransform);

    static const float distanceFactor = std::sqrt(window.getSize().x * window.getSize().x + window.getSize().y * window.getSize().y)
                                         * window.getSize().x + window.getSize().y * window.getSize().y / 2.0f;
    float colorCorrection = std::max(0.65f, 1.0f - obstacle.getDistanceSquaredToPlayer() / distanceFactor);

    toTransform.getBody()->setFillColor(sf::Color(255 * colorCorrection, 255 * colorCorrection, 255 * colorCorrection, 255 * colorCorrection));
    toTransform.getBody()->setScale(colorCorrection, colorCorrection);
}