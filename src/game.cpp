#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "game.h"
#include "obstacle.h"
#include "player.h"
#include "charge.h"
#include "settings.h"

extern const char debug;
extern const char targetFramerate;
extern const float windowWidth;
extern const float windowHeight;
extern const float arrowWidth;

// Create window
Game::Game()
    : window(sf::VideoMode(windowWidth, windowHeight), "Charge game", sf::Style::Default), player(Player(7.0, 1.0, 15.0, sf::Vector2f(500.0f, 250.0f)))
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
            break;
        default:
            break;
        }
    }
}

// Handles input from player
void Game::handleInput()
{
    while (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        pause();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f zeroSpeed(0.0f, 0.0f);
        player.setSpeed(zeroSpeed);
        player.setPosition(sf::Vector2f((float)mousePos.x, (float)mousePos.y));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        terminate();
        Game newGame;
        newGame.run();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;
        addObstacle(Obstacle(7.0f, -1500.0f, mousePos, sf::Color::Blue));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;
        addObstacle(Obstacle(7.0f, 1500.0f, mousePos, sf::Color::Green));
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
    for (Obstacle obstacle : obstacles)
        obstacle.draw(window);
    player.draw(window);
    window.display();
}

// Add object to game instance
void Game::addObstacle(Obstacle newObstacle)
{
    // obstacles.insert(obstacles.begin(), newObstacle);
    obstacles.push_back(newObstacle);
    if (debug == 3)
        std::cout << "obstacle count:\t" << obstacles.size() << std::endl;
}

// Set starting speed for player from mouse input
void Game::setStartSpeed()
{
    bool isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getPosition().x) < player.getRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getPosition().y) < player.getRadius();
    while (!(sf::Mouse::isButtonPressed((sf::Mouse::Left)) && isMouseOnPlayer))
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
    while (sf::Mouse::isButtonPressed((sf::Mouse::Left)))
    {
        handleEvent();
        handleInput();
        render();
        window.draw(arrow);
        window.display();
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
    player.setSpeed(startSpeed);
}

// Frees all resources, closes window
void Game::terminate()
{
    window.close();
    obstacles.clear();
}

// Pauses everything
void Game::pause()
{
    clock.restart();
}

// Run method with game loop
void Game::run()
{
    setStartSpeed();

    clock.restart();
    while (window.isOpen())
    {
        while (!window.hasFocus() && window.isOpen())
            pause();

        deltaTime = clock.restart().asSeconds();
        renderDeltaTime += deltaTime;
        handleEvent();
        handleInput();
        physics.updatePlayer(player, deltaTime, obstacles);

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
