#pragma once
#include <vector>

#include "player.h"
#include "obstacle.h"

class PhysicsEngine
{
private:
    // Physical constants
    const float k;
    const float frictionCoeff;
    const float g;
    const sf::Vector2f calculateElectricForce() const;
    const sf::Vector2f calculateFrictionForce() const;
    void checkCollision();
public:
    // proper k = 8.988e-9
    PhysicsEngine(const float coulombConst = 8.988e-4f, const float frictionCoeff = 10.0f, const float g = 9.81f);
    void updatePlayer();
};