#pragma once
#include <vector>

#include "player.h"
#include "obstacle.h"

/**
 * @class PhysicsEngine
 * @brief Represents a physics engine for simulating physical forces and collisions.
 *
 * The PhysicsEngine class provides functionality for calculating electric forces, friction forces,
 * and checking collisions. It also allows updating the player's physics state.
 */
class PhysicsEngine
{
private:
    // Physical constants
    const float k; ///< Coulomb constant
    const float frictionCoeff; ///< Coefficient of friction
    const float g; ///< Acceleration due to gravity

    /**
     * @brief Calculates the electric force acting on an object by all obstacles and sums them.
     * @return The electric force as a 2D vector (sf::Vector2f).
     */
    const sf::Vector2f calculateElectricForce() const;

    /**
     * @brief Calculates the friction force acting on an object.
     * @return The friction force as a 2D vector.
     */
    const sf::Vector2f calculateFrictionForce() const;

    /**
     * @brief Checks for collisions between Player and walls and obstacles.
     */
    void checkCollision();

public:
    /**
     * @brief Constructs a new PhysicsEngine object.
     * @param coulombConst The Coulomb constant (default: 8.988e-4f).
     * @param frictionCoeff The coefficient of friction (default: 10.0f).
     * @param g The acceleration due to gravity (default: 9.81f).
     */
    PhysicsEngine(const float coulombConst = 8.988e2f, const float frictionCoeff = 10.0f, const float g = 9.81f);

    /**
     * @brief Updates the player's movement.
     */
    void updatePlayer();
};