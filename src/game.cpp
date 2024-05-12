#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "game.h"
#include "obstacle.h"
#include "player.h"
#include "charge.h"
#include "level.h"
#include "levelManager.h"
#include "settings.h"

extern const char debug;
extern const unsigned int targetFramerate;
extern const float windowWidth;
extern const float windowHeight;
extern const float arrowWidth;
extern const double keyStickDuration;

// Create window
Game::Game(Level loadedLevel)
    : window(sf::VideoMode(loadedLevel.getSize().x, loadedLevel.getSize().y), "Charge game: " + loadedLevel.getName(), sf::Style::Default), player(Player(window, 7.0, 1.0, 15.0, loadedLevel.getPlayerStartPos())), level(loadedLevel), physics(window, isPause, player, level.getObstacles())
{
    window.setFramerateLimit(targetFramerate);
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
            break;
        case sf::Event::KeyPressed:
            if (evnt.key.code == sf::Keyboard::Escape)
                isPause = !isPause;
            if (evnt.key.code == sf::Keyboard::S)
            {
                level.setPlayerStartPos(player.getPosition());
                LevelManager::getInstance()->saveLevel(level);
                LevelManager::getInstance()->updateIndex();
            }
            if (evnt.key.code == sf::Keyboard::R)
            {
                terminate();
                Game newGame;
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    newGame.level = LevelManager::getInstance()->loadLevel(0);
                }
                newGame.run();
            }

        default:
            break;
        }
    }
}

// Handles input from player
void Game::handleInput()
{
    if (!window.hasFocus())
        return;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Vector2f zeroSpeed(0.0f, 0.0f);
        player.setSpeed(zeroSpeed);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        player.setPosition(window, mousePosFloat);
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
        level.addObstacle(Obstacle(window, 7.0f, -1500.0f, mousePos));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;
        level.addObstacle(Obstacle(window, 7.0f, 1500.0f, mousePos));
    }
}

void Game::resizeView(const sf::Event &evnt)
{
    sf::FloatRect visibleArea(0.0f, 0.0f, evnt.size.width, evnt.size.height);
    window.setView(sf::View(visibleArea));
    level.setSize(window.getSize());
}

void Game::resizeView(const sf::Vector2u &newSize)
{
    window.setSize(newSize);
    sf::FloatRect visibleArea(0.0f, 0.0f, newSize.x, newSize.y);
    window.setView(sf::View(visibleArea));
    level.setSize(window.getSize());
}

// Render method
void Game::render()
{
    window.clear();
    // TODO: Don't draw every obstacle every frame
    for (Obstacle obstacle : level.getObstacles())
        obstacle.draw(window);
    for (const sf::Drawable *drawablePtr : drawables)
        window.draw(*drawablePtr);
    player.draw(window);
    window.display();
}

// Set starting speed for player from mouse input
void Game::setStartSpeed()
{
    bool isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getPosition().x) < player.getRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getPosition().y) < player.getRadius();
    while (!(sf::Mouse::isButtonPressed((sf::Mouse::Left)) && isMouseOnPlayer) && window.isOpen())
    {
        handleEvent();
        handleInput();
        render();
        isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getPosition().x) < player.getRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getPosition().y) < player.getRadius();
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
        arrow.setPosition(player.getPosition());
        arrow.setSize(sf::Vector2f(std::sqrt(startSpeed.x * startSpeed.x + startSpeed.y * startSpeed.y), arrowWidth));
        float angle = std::atan2((sf::Mouse::getPosition(window).y - player.getPosition().y), (sf::Mouse::getPosition(window).x - player.getPosition().x)) * 180.0f / M_PI;
        arrow.setRotation(angle);
        startSpeed.x = (player.getPosition().x - sf::Mouse::getPosition(window).x);
        startSpeed.y = (player.getPosition().y - sf::Mouse::getPosition(window).y);
        if (debug == 4)
            std::cout << "Start speed:\t" << std::sqrt(startSpeed.x * startSpeed.x + startSpeed.y * startSpeed.y)
                      << "\t\tx: " << startSpeed.x << "\ty: " << startSpeed.y << std::endl;
    }
    drawables.pop_back();
    player.setSpeed(startSpeed);
}

// Frees all resources, closes window
void Game::terminate()
{
    window.close();
    level.clearObstacles();
}

// Run method with game loop
void Game::run()
{
    resizeView(level.getSize());
    sf::Vector2f playerStartPos(level.getPlayerStartPos());
    player.setPosition(window, playerStartPos);
    setStartSpeed();
    clock.restart();
    while (window.isOpen())
    {
        if (!window.hasFocus())
            isPause = true;

        deltaTime = clock.restart().asSeconds();
        handleEvent();
        handleInput();
        if (!isPause)
            physics.updatePlayer(deltaTime);

        if (debug == 1)
        {
            std::cout << "fps:\t" << 1 / renderDeltaTime << std::endl;
        }
        renderDeltaTime = 0;
        render();
    }
}
