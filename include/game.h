#pragma once
#include <SFML/Graphics.hpp>

#include "physics.h"
#include "player.h"
#include "obstacle.h"
#include "level.h"

class Game
{
private:
    // Instance of window
    sf::RenderWindow window;
    // Player in the game
    Player player;
    // Level currently loaded
    Level level;
    // Vector of drawable references
    std::vector<const sf::Drawable *> drawables;
    // Clock for measuring deltaTime
    sf::Clock clock;
    // Determines if simulation runs or not
    bool isPause = false;
    // deltaTime used for simulation
    double deltaTime = 0.0f;
    // Render deltaTime for framerate
    double renderDeltaTime = 0.0f;
    // Connected physics engine
    PhysicsEngine physics;
    // Handles input from player
    void handleInput();
    // Renders every object ??
    void render();
    // Handles window events such as close, resize...
    void handleEvent();
    // Handles resize event
    void resizeView(const sf::Event &evnt);
    void resizeView(const sf::Vector2u &newSize);
    // Set starting speed for player from mouse input
    void setStartSpeed();

public:
    // Constructor
    Game(Level loadedLevel = Level());
    // Destructor
    ~Game() { terminate(); }
    // Main game loop
    void run();
    // Terminate: close window and free resources
    void terminate();
};