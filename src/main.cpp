#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>

#include "obstacle.h"
#include "player.h"
#include "charge.h"
#include "level.h"
#include "levelManager.h"
#include "settings.h"
#include "physics.h"

extern const char debug;
extern const unsigned int targetFramerate;
extern const unsigned windowWidth;
extern const unsigned windowHeight;
extern const float arrowWidth;

// Instance of window
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Charge game: Main menu", sf::Style::Titlebar | sf::Style::Close);
// Player in the game
Player player;
// Level currently loaded
Level level;
// Vector of drawable references
std::vector<const sf::Drawable *> drawables;
// Clock for measuring deltaTime
sf::Clock gameClock;
// Determines if simulation runs or not
bool isPause = false;
// deltaTime used for simulation
float deltaTime = 0.0f;
// Render deltaTime for framerate
double renderDeltaTime = 0.0f;
// Connected physics engine
PhysicsEngine physics;

void runGame();
void resizeView(const sf::Vector2u &newSize);

// Resets drawables, window and player
void startGame()
{
    resizeView(level.getSize());
    window.setTitle("Charge game: " + level.getName());
    sf::Vector2f playerStartPos = level.getPlayerStartPos();
    player.setPosition(playerStartPos);
    drawables.clear();
    for (const std::shared_ptr<Obstacle> &obstacle : level.getObstacles())
    {
        drawables.push_back(&obstacle.get()->getBody());
    }
    drawables.push_back(&player.getBody());
}

// Frees all resources, closes window
void terminate()
{
    window.close();
}

void resizeView(const sf::Event &evnt)
{
    sf::FloatRect visibleArea(0.0f, 0.0f, evnt.size.width, evnt.size.height);
    window.setView(sf::View(visibleArea));
    level.setSize(window.getSize());
}

void resizeView(const sf::Vector2u &newSize)
{
    window.setSize(newSize);
    sf::FloatRect visibleArea(0.0f, 0.0f, newSize.x, newSize.y);
    window.setView(sf::View(visibleArea));
    level.setSize(window.getSize());
}

// Handles window events such as close, resize...
void handleEvent()
{
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        switch (evnt.type)
        {
        case sf::Event::Closed:
            terminate();
            break;
            // TODO: resize event handle
        case sf::Event::Resized:
            resizeView(evnt);
            break;
        case sf::Event::KeyPressed:
            if (evnt.key.code == sf::Keyboard::Escape)
                isPause = !isPause;
            if (evnt.key.code == sf::Keyboard::F)
            {
                level.setPlayerStartPos(player.getBody().getPosition());
                LevelManager::getInstance()->saveLevel(level);
                LevelManager::getInstance()->updateIndex();
            }
            if (evnt.key.code == sf::Keyboard::R)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        level = LevelManager::getInstance()->loadLevel();
                    }
                    startGame();
                }
                runGame();
            }

        default:
            break;
        }
    }
}

// Handles input from player
void handleInput()
{
    if (!window.hasFocus())
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Vector2f zeroSpeed(0.0f, 0.0f);
        player.setSpeed(zeroSpeed);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        player.setPosition(mousePosFloat);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        sf::Vector2f zeroSpeed(0.0f, 0.0f);
        player.setSpeed(zeroSpeed);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;
        Obstacle newObstacle(window, 7.0f, -1500.0f, mousePos);
        level.addObstacle(newObstacle);
        drawables.push_back(&level.getObstacles().back().get()->getBody());
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;
        Obstacle newObstacle(window, 7.0f, 1500.0f, mousePos);
        level.addObstacle(newObstacle);
        drawables.push_back(&level.getObstacles().back().get()->getBody());
    }
}

// Render method
void render()
{
    window.clear();
    for (const sf::Drawable *drawablePtr : drawables)
        window.draw(*drawablePtr);

    window.display();
}

// Set starting speed for player from mouse input
void setStartSpeed()
{
    bool isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getBody().getPosition().x) < player.getBody().getRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getBody().getPosition().y) < player.getBody().getRadius();
    while (!(sf::Mouse::isButtonPressed((sf::Mouse::Left)) && isMouseOnPlayer) && window.isOpen())
    {
        handleEvent();
        handleInput();
        render();
        isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getBody().getPosition().x) < player.getBody().getRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getBody().getPosition().y) < player.getBody().getRadius();
    }

    sf::Vector2f startSpeed(0.0f, 0.0f);
    sf::RectangleShape arrow(sf::Vector2f(0.0f, arrowWidth));
    arrow.setFillColor(sf::Color::Magenta);
    arrow.setOrigin(0.0f, arrowWidth / 2);
    drawables.push_back(&arrow);

    while (sf::Mouse::isButtonPressed((sf::Mouse::Left)))
    {
        handleEvent();
        handleInput();
        render();
        arrow.setPosition(player.getBody().getPosition());
        arrow.setSize(sf::Vector2f(std::sqrt(startSpeed.x * startSpeed.x + startSpeed.y * startSpeed.y), arrowWidth));
        float angle = std::atan2((sf::Mouse::getPosition(window).y - player.getBody().getPosition().y), (sf::Mouse::getPosition(window).x - player.getBody().getPosition().x)) * 180.0f / M_PI;
        arrow.setRotation(angle);
        startSpeed.x = (player.getBody().getPosition().x - sf::Mouse::getPosition(window).x);
        startSpeed.y = (player.getBody().getPosition().y - sf::Mouse::getPosition(window).y);
        if (debug == 4)
            std::cout << "Start speed:\t" << std::sqrt(startSpeed.x * startSpeed.x + startSpeed.y * startSpeed.y)
                      << "\t\tx: " << startSpeed.x << "\ty: " << startSpeed.y << std::endl;
    }
    drawables.pop_back();
    player.setSpeed(startSpeed);
}

// Run method with game loop
void runGame()
{
    setStartSpeed();
    gameClock.restart();
    while (window.isOpen())
    {
        if (!window.hasFocus())
            isPause = true;

        deltaTime = gameClock.restart().asSeconds();

        if (debug == 1)
            std::cout << "dT:\t" << deltaTime << std::endl;

        handleEvent();
        handleInput();
        if (!isPause)
            physics.updatePlayer();

        render();
    }
}

int main()
{
    window.setFramerateLimit(targetFramerate);
    window.setSize(sf::Vector2u(windowWidth, windowHeight));
    window.setTitle("Charge game: Main menu");

    level = LevelManager::getInstance()->loadLevel(0);

    startGame();

    runGame();

    return 0;
}