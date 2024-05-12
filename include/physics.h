#pragma once
#include <vector>

#include "player.h"
#include "obstacle.h"

class PhysicsEngine
{
private:
    // Reference to game context (window, player, obstacles)
    const sf::RenderWindow &window;
    bool &isPause;
    Player &player;
    const std::vector<Obstacle>& obstacles;
    // Physical constants
    const float k;
    const float frictionCoeff;
    const float g;
    const sf::Vector2f calculateElectricForce() const;
    const sf::Vector2f calculateFrictionForce() const;
    void checkCollision();
public:
    // proper k = 8.988e-9
    PhysicsEngine(const sf::RenderWindow& window, bool &isPause, Player& player, const std::vector<Obstacle>& obstacles, const float coulombConst = 8.988e-4f, const float frictionCoeff = 10.0f, const float g = 9.81f);
    void updatePlayer(const double deltaTime);
};