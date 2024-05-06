#pragma once
#include <vector>

#include "player.h"
#include "obstacle.h"

class PhysicsEngine
{
private:
    // Coulomb constant
    const float k;
    const float frictionCoeff;
    const float g;

public:
    // proper k = 8.988e-9
    PhysicsEngine(const float coulombConst = 8.988e-5f, const float frictionCoeff = 10.0f, const float g = 9.81f);
    void updatePlayer(Player &player, const double deltaTime, const std::vector<Obstacle>& obstacles);
};