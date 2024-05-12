#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

#include "obstacle.h"
#include "player.h"
#include "level.h"
#include "settings.h"

extern const char debug;

Level::Level(const std::string &levelName, const sf::Vector2u &levelSize, const std::vector<Obstacle> &obstacles, const sf::Vector2f &playerStartPos)
    : name(levelName), size(levelSize), obstacles(obstacles), playerStartPos(playerStartPos)
{
}

// Add obstacle to level
void Level::addObstacle(const Obstacle &newObstacle)
{
    obstacles.push_back(newObstacle);
    if (debug == 3)
        std::cout << "obstacle count:\t" << obstacles.size() << std::endl;
}