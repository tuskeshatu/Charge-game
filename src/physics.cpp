#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>

#include "obstacle.h"
#include "physics.h"
#include "settings.h"

extern const char debug;

PhysicsEngine::PhysicsEngine(const float coulombConst, const float frictionCoeff, const float g) : k(coulombConst), frictionCoeff(frictionCoeff), g(g)
{
}

void PhysicsEngine::updatePlayer(Player &player, const double deltaTime, const std::vector<Obstacle> &obstacles)
{
    // Calculate force vector for each obstacle with the player and sum them
    // Formula: F(r) = k * q_player sum(q_obstacle * (ri / abs(ri)^3))
    // Where ri is a vector pointing from the obstacle to the player
    sf::Vector2f totalForce(0.0, 0.0);

    // Calculate force vector for each obstacle with the player and sum them
    // Formula: F(r) = k * q_player sum(q_obstacle * (ri / abs(ri)^3))
    // Where ri is a vector pointing from the obstacle to the player
    for (const Obstacle &obstacle : obstacles)
    {
        // r vector pointing from the obstacle to the player
        sf::Vector2f ri = player.getPosition() - obstacle.getPosition();
        // Devide ri by 1000 to get realistic distances
        ri.x /= 1000;
        ri.y /= 1000;
        double riLengthSquared = ri.x * ri.x + ri.y * ri.y;

        // In real physics its divided by the cube of riLength
        // For better gameplay I broke physics, only divided by the sqere :)
        // x component
        totalForce.x += obstacle.getElectricCharge() * (ri.x / (riLengthSquared * std::sqrt(riLengthSquared)));
        // y component
        totalForce.y += obstacle.getElectricCharge() * (ri.y / (riLengthSquared * std::sqrt(riLengthSquared)));
    }
    // Multiply the sum to get total force
    totalForce.x *= k * player.getElectricCharge();
    totalForce.y *= k * player.getElectricCharge();

    // Subtract a friction force proportionally linked to the speed
    totalForce.x -= (frictionCoeff * player.getSpeed().x / playerMaxSpeed) * player.getMass() * g;
    totalForce.y -= (frictionCoeff * player.getSpeed().y / playerMaxSpeed) * player.getMass() * g;

    if (debug == 2)
        std::cout
            << "total force:\t" << std::sqrt(totalForce.x * totalForce.x + totalForce.y * totalForce.y)
            << "\t\tx: " << totalForce.x << "\ty: " << totalForce.y << std::endl;

    // To get acceleration divide force by mass
    sf::Vector2f acceleration(0.0, 0.0);
    acceleration.x = totalForce.x / player.getMass();
    acceleration.y = totalForce.y / player.getMass();

    // Update player movement
    player.updateMovement(acceleration, deltaTime);
}