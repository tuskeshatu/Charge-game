#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>

#include "obstacle.h"
#include "physics.h"
#include "settings.h"
#include "level.h"

extern const char debug;

extern sf::RenderWindow window;
extern Player player;
extern Level level;
extern bool isPause;


// Construct based on provided constants.
// Not singleton to allow constants to change (it might be interesting gameplay as a later addition)
PhysicsEngine::PhysicsEngine(const float coulombConst, const float frictionCoeff, const float g)
    : k(coulombConst), frictionCoeff(frictionCoeff), g(g)
{
}

// Calculate electric force
const sf::Vector2f PhysicsEngine::calculateElectricForce() const
{

    // Calculate force vector for each obstacle with the player and sum them
    // Formula: F(r) = k * q_player sum(q_obstacle * (ri / abs(ri)^3))
    // Where ri is a vector pointing from the obstacle to the player
    sf::Vector2f totalForce(0.0, 0.0);

    // Calculate force vector for each obstacle with the player and sum them
    // Formula: F(r) = k * q_player sum(q_obstacle * (ri / abs(ri)^3))
    // Where ri is a vector pointing from the obstacle to the player
    for (const std::shared_ptr<Obstacle> &obstacle : level.getObstacles())
    {
        // r vector pointing from the obstacle to the player
        sf::Vector2f ri = player.getBody()->getPosition() - obstacle.get()->getBody()->getPosition();
        // Devide ri by 1000 to get realistic distances
        ri.x /= 1000;
        ri.y /= 1000;
        double riLengthSquared = ri.x * ri.x + ri.y * ri.y;

        // It is divided by the cube of riLength
        // x component
        totalForce.x += obstacle.get()->getElectricCharge() * (ri.x / (riLengthSquared * std::sqrt(riLengthSquared)));
        // y component
        totalForce.y += obstacle.get()->getElectricCharge() * (ri.y / (riLengthSquared * std::sqrt(riLengthSquared)));
    }
    // Multiply the sum to get total force
    totalForce.x *= k * player.getElectricCharge();
    totalForce.y *= k * player.getElectricCharge();

    return totalForce;
}

// Calculate friction force
const sf::Vector2f PhysicsEngine::calculateFrictionForce() const
{
    // Friction is linearly proportional to the speed of the player (similar to drag irl)
    return sf::Vector2f((frictionCoeff * player.getSpeed().x / playerMaxSpeed) * player.getMass() * g,
                        (frictionCoeff * player.getSpeed().y / playerMaxSpeed) * player.getMass() * g);
}

// Checks for collisions between Player and walls and obstacles.
void PhysicsEngine::checkCollision()
{
    // Get player position
    const sf::Vector2f playerPos(player.getBody()->getPosition());
    // Check for each obstacle
    for (const std::shared_ptr<Obstacle> &obstacle : level.getObstacles())
    {
        sf::Vector2f obstaclePos(obstacle.get()->getBody()->getPosition());
        // If the length of the vector between the obstacle and the player is shorter than the radius they are colliding
        // To avoid calculating sqrt basically: x^2+y^2 <= (r1 + r2)^2
        if ((playerPos.x - obstaclePos.x) * (playerPos.x - obstaclePos.x) + (playerPos.y - obstaclePos.y) * (playerPos.y - obstaclePos.y) <= (player.getBody()->getRadius() + obstacle.get()->getBody()->getRadius()) * (player.getBody()->getRadius() + obstacle.get()->getBody()->getRadius()))
            isPause = true;
    }

    // Check collision with walls of the window, simulate perfectly elastic collision, where walls have infinite weight 
    // So just set the corresponding component of player's speed to its opposite
    sf::Vector2f windowSize(window.getSize());
    sf::Vector2f playerSpeed(player.getSpeed());
    if (playerPos.x < 0 || playerPos.x > windowSize.x)
        playerSpeed.x = -playerSpeed.x;
    if (playerPos.y < 0 || playerPos.y > windowSize.y)
        playerSpeed.y = -playerSpeed.y;

    // And finally set the speed
    player.setSpeed(playerSpeed);
}

// Update player movement
void PhysicsEngine::updatePlayer()
{
    // Initialize total force
    sf::Vector2f totalForce(0.0, 0.0);

    // Add the electric part
    totalForce += calculateElectricForce();

    // Subtract a friction force proportionally linked to the speed
    totalForce -= calculateFrictionForce();

    if (debug == 2)
        std::cout << "total force:\t" << std::sqrt(totalForce.x * totalForce.x + totalForce.y * totalForce.y)
                  << "\t\tx: " << totalForce.x << "\ty: " << totalForce.y << std::endl;

    // To get acceleration divide force by mass
    sf::Vector2f acceleration(0.0, 0.0);
    acceleration.x = totalForce.x / player.getMass();
    acceleration.y = totalForce.y / player.getMass();

    // Update player movement
    player.updateMovement(acceleration);
    
    // And check for collisions
    checkCollision();
}