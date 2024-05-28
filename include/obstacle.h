#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"
#include "obstacleAnimation.h"
#include "animation.h"

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

    const float collisionBox; /**< The collision box of the obstacle */
    std::shared_ptr<sf::CircleShape> body; /**< The body of the obstacle */
    
    sf::Vector2f vectorToPlayer; /**< The vector pointing from the obstacle to the player */
    float distanceSquaredToPlayer; /**< The distance to the player */

    ObstacleAnimation animation; /**< The animation of the obstacle */

    /**
     * @brief Sets the distance to the player.
     * 
     * @param newDistance The new distance to the player.
     */
    void updateDistanceSquaredToPlayer();

    /**
     * @brief Updates the vector pointing from the obstacle to the player.
     *
     */
    void updateVectorToPlayer();

    /**
     * @brief Updates the animation of the obstacle.
     * 
     */
    void updateAnimation() {animation.applyTransform(*this);}

public:

    /**
     * @brief Constructs an Obstacle object with the given parameters.
     * 
     * @param radius The radius of the obstacle (default: 100.0f).
     * @param charge The charge of the obstacle (default: 10.0).
     * @param pos The position of the obstacle (default: sf::Vector2f(250.0, 250.0)).
     */
    Obstacle(const float radius = 100.0f, const double charge = 1.0f, const sf::Vector2f &pos = sf::Vector2f(250.0, 250.0));

    /**
     * @brief Returns a constant reference to the body of the obstacle.
     * 
     * @return const sf::CircleShape& A constant reference to the body of the obstacle.
     */
    const std::shared_ptr<sf::CircleShape> &getBody() const override { return body; }

    /**
     * @brief Returns a constant reference to the collision box of the obstacle.
     * 
     * @return const sf::CircleShape& A constant reference to the collision box of the obstacle.
     */
    const float getCollisionRadius() const { return collisionBox; }

    /**
     * @brief Sets the position of the obstacle.
     * 
     * @param newPos The new position of the obstacle.
     */
    void setPosition(sf::Vector2f &newPos) override;

    /**
     * @brief Returns the vector pointing from the obstacle to the player.
     * 
     * @return const sf::Vector2f& The vector pointing from the obstacle to the player.
     */
    const sf::Vector2f &getVectorToPlayer() const { return vectorToPlayer; }

    void updateObstacle()
    {
        updateVectorToPlayer();
        updateDistanceSquaredToPlayer();
        updateAnimation();
    }

    /**
     * @brief Returns the distance squared to the player.
     * 
     * @return float The distance to the player.
     */
    float getDistanceSquaredToPlayer() const { return distanceSquaredToPlayer; }
};