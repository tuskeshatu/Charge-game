#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "physics.h"
#include "player.h"
#include "obstacle.h"
class Game
{
private:
    // Instance of window
    sf::RenderWindow window;
    // Clock for measuring deltaTime
    sf::Clock clock;
    // deltaTime used for simulation
    double deltaTime = 0.0f;
    // Render deltaTime for framerate
    double renderDeltaTime = 0.0f;
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
    // Set starting speed for player from mouse input
    void setStartSpeed();
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
    // Pauses everything
    void pause();
};