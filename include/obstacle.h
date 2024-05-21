#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"

/**
 * @class Obstacle
 * @brief Represents an obstacle in the program.
 * 
 * This class is derived from the Charge class and represents an obstacle as a circle (similar to a point charge).
 * It contains an sf::CircleShape object to represent the body of the obstacle.
 */
class Obstacle : public Charge
{
private:

    /**
     * @brief Represents a circle shape in SFML.
     *
     * The sf::CircleShape class is a drawable object that represents a circle.
     * It can be used to draw circles of various sizes and colors on an SFML window.
     */
    std::shared_ptr<sf::CircleShape> body;

public:

    /**
     * @brief Constructs an Obstacle object with the given parameters.
     * 
     * @param radius The radius of the obstacle (default: 100.0f).
     * @param charge The charge of the obstacle (default: 10.0).
     * @param pos The position of the obstacle (default: sf::Vector2f(250.0, 250.0)).
     */
    Obstacle(const float radius = 100.0f, const double charge = 10.0, const sf::Vector2f &pos = sf::Vector2f(250.0, 250.0));

    /**
     * @brief Returns a constant reference to the body of the obstacle.
     * 
     * @return const sf::CircleShape& A constant reference to the body of the obstacle.
     */
    const std::shared_ptr<sf::CircleShape> &getBody() const override { return body; }

    /**
     * @brief Sets the position of the obstacle.
     * 
     * @param newPos The new position of the obstacle.
     */
    void setPosition(sf::Vector2f &newPos) override;
};