#pragma once
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "player.h"
#include "obstacle.h"
class Game
{
private:
    // Instance of window
    sf::RenderWindow window;
    // Connected physics engine
    PhysicsEngine physics;
    // Vector of obstacles in game
    std::vector<Obstacle> obstacles;
    // Player in the game
    Player player;
    // Handles input from player
    void handleInput();
    // Renders every object ??
    void render();
    // Handles window events such as close, resize...
    void handleEvent();
    // Handles resize event
    void resizeView(sf::Event);
public:
    // Constructor
    Game();
    // Destructor
    ~Game() { terminate(); }
    // Main game loop
    void run();
    // Add object to game instance
    void addObstacle(Obstacle);
    // Terminate: close window and free resources
    void terminate();
};