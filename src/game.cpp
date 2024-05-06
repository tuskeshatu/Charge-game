#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>

#include "game.h"
#include "obstacle.h"
#include "player.h"
#include "charge.h"
#include "settings.h"

extern const char debug;
extern const char targetFramerate;
extern const float windowWidth;
extern const float windowHeight;

// Create window
Game::Game()
    : window(sf::VideoMode(windowWidth, windowHeight), "Charge game", sf::Style::Default)
    , player(Player(7.0, 1.0, 15.0, sf::Vector2i(500, 250)))
{
}

// Handles window events such as close, resize...
void Game::handleEvent()
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
            //float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
            //window.setSize(sf::Vector2u(windowHeight * aspectRatio, windowHeight));
            break;
        default:
            break;
        }
    }
}

void Game::resizeView(sf::Event evnt)
{
    sf::FloatRect visibleArea(0.0f, 0.0f, evnt.size.width, evnt.size.height);
    window.setView(sf::View(visibleArea));
}

// Render method
void Game::render()
{
    window.clear();
    // TODO: Don't draw every obstacle every frame
    for (Charge obstacle : obstacles)
        obstacle.draw(window);
    player.draw(window);
    window.display();
}

// Add object to game instance
void Game::addObstacle(Obstacle newObstacle)
{
    //obstacles.insert(obstacles.begin(), newObstacle);
    obstacles.push_back(newObstacle);
    if (debug == 3)
        std::cout << "obstacle count:\t" << obstacles.size() << std::endl;
}

// Handles input from player
void Game::handleInput()
{
    //TODO: only place one object for each mouse click
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        player.setSpeed(sf::Vector2f(0.0f, 0.0f));
        player.setPosition(sf::Vector2f((float)mousePos.x, (float)mousePos.y));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        addObstacle(Obstacle(7, -1500.0, mousePos, sf::Color::Blue));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        addObstacle(Obstacle(7, 1500.0, mousePos, sf::Color::Green));
    }
}



// Frees all resources, closes window
void Game::terminate()
{
    window.close();
    obstacles.clear();
}



// Run method
void Game::run()
{
    double deltaTime = 0.0f;
    double renderDeltaTime = 0.0f;
    sf::Clock clock;

    // Get event for resizing and closing
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        renderDeltaTime += deltaTime;
        handleEvent();
        handleInput();
        physics.updatePlayer(player, deltaTime, obstacles);

        //
        if (1 / renderDeltaTime < targetFramerate)
        {
            if (debug == 1)
            {
                std::cout << "fps:\t" << 1 / renderDeltaTime << std::endl;
            }
            renderDeltaTime = 0;
            render();
        }
    }
}
