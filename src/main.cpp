#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>
#include <exception>

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
extern const unsigned menuTitleSize;
extern const unsigned levelNameCharLimit;

/**
 * @brief The main window of the application.
 *
 * The sf::RenderWindow class provides a window for rendering and displaying graphics.
 * It is the main class for creating and managing the application window.
 */
sf::RenderWindow window;

/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * The Player class encapsulates the properties and behaviors of a player in the game.
 * It provides methods to interact with the player, such as setting the player's name,
 * getting the player's score, and updating the player's position.
 */
Player player;

/**
 * @class Level
 * @brief Represents a level in a game.
 *
 * The Level class is responsible for managing the game level, including loading
 * level data, updating game objects, and rendering the level.
 */
Level level;

/**
 * @brief A vector of pointers to constant sf::Drawable objects.
 *
 * This vector is used to store pointers to objects that inherit from sf::Drawable,
 * such as sf::CircleShape or sf::Text. The pointers are constant, meaning that the
 * objects they point to cannot be modified through these pointers. It is used by render() to render objects.
 */
std::vector<std::shared_ptr<sf::Drawable>> gameDrawables;

/**
 * @brief A vector of pointers to constant sf::Drawable objects.
 *
 * This vector is used to store pointers to objects that inherit from sf::Drawable,
 * such as sf::CircleShape or sf::Text. The pointers are constant, meaning that the
 * objects they point to cannot be modified through these pointers. It is used by render() to render objects.
 */
std::vector<std::shared_ptr<sf::Drawable>> menuDrawables;

/**
 * @brief The clock object for the game. Measures deltaTime.
 */
sf::Clock gameClock;

/**
 * @brief A boolean variable indicating whether the program is in a paused state.
 *
 * This variable is used to control the pause state of the program. When set to true, the program is considered to be paused.
 * When set to false, the program is considered to be running.
 */
bool isPause = false;

/**
 * @brief Indicates whether the program is in editor mode or not.
 *
 * This variable is used to determine whether the program is currently running in editor mode or not.
 * When set to true, the program performs certain actions specific to the editor mode.
 * By default, it is set to false.
 */
bool isEditorMode = false;

/**
 * @brief The time elapsed since the last simulation iteration.
 *
 * This variable represents the time difference between the current iteration and the previous iteration.
 * It is used to control the speed of the physics simulation.
 */
float deltaTime = 0.0f;

/**
 * @class PhysicsEngine
 * @brief Represents a physics engine for simulating physical interactions.
 *
 * The PhysicsEngine provides interface for simulating forces.
 */
PhysicsEngine physics;

/**
 * @brief The `sf::Font` class is a utility class for loading and using fonts.
 *
 * This represents the font used across the whole game.
 */
sf::Font font;

// Declaration of functions
void runGame();
void resizeView(const sf::Vector2u &newSize);
void startGame();
void displayPauseOverlay();
void saveMenu();
void setStartSpeed();

/**
 * @brief Resizes the view of the window and updates the level size accordingly.
 *
 * @param evnt The event containing the new size of the window.
 */
void resizeView(const sf::Event &evnt)
{
    // Create rectangle for view and create view
    sf::FloatRect visibleArea(0.0f, 0.0f, evnt.size.width, evnt.size.height);
    window.setView(sf::View(visibleArea));
    // Set level size accordingly
    level.setSize(window.getSize());
}

/**
 * @brief Resizes the view of the window and adjusts the level size accordingly.
 *
 * @param newSize The new size of the view.
 */
void resizeView(const sf::Vector2u &newSize)
{
    // Set size and view
    window.setSize(newSize);
    sf::FloatRect visibleArea(0.0f, 0.0f, newSize.x, newSize.y);
    window.setView(sf::View(visibleArea));
    // Set level size accordingly
    level.setSize(window.getSize());
}

/**
 * @brief Handles game events such as window close, resize, and key press.
 *
 * This function is responsible for handling various game events, including window close,
 * window resize, and key press events. It performs specific actions based on the type of event
 * received, such as clearing obstacles, closing the window, toggling pause mode, and loading levels.
 */
void handleGameEvent()
{
    // Create event object and poll for events
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        switch (evnt.type)
        {
            // Window is closed, vectors are cleared, program terminates
        case sf::Event::Closed:
            level.clearObstacles();
            gameDrawables.clear();
            menuDrawables.clear();
            window.close();
            exit(0);
            break;
            // Window is resized
        case sf::Event::Resized:
            resizeView(evnt);
            break;
            // If key press occured (event is used for detecting key presses to avoid sticky keys)
        case sf::Event::KeyPressed:
            // Escape pauses
            if (evnt.key.code == sf::Keyboard::Escape)
                isPause = !isPause;
            // R resets based on modifyer keys
            if (evnt.key.code == sf::Keyboard::R)
            {
                // LCtrl + R: If in editor mode, this allows the player to not reset level, but set start speed
                if (isEditorMode && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    setStartSpeed();
                    runGame();
                }
                // In normal case (not in editor mode and if in editor mode only if R is pressed) just resets game.
                startGame();
            }

        default:
            break;
        }
    }
}

/**
 * @brief Handles menu events.
 *
 * This function is responsible for handling events related to the menu.
 * It listens for events such as window close and key press.
 * If the window is closed, it clears the obstacles, game drawables, and menu drawables.
 * It also closes the window and exits the program. If the escape key is pressed, it toggles the pause state.
 */
void handleMenuEvent()
{
    // Poll for events
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        switch (evnt.type)
        {
            // Close event
        case sf::Event::Closed:
            level.clearObstacles();
            gameDrawables.clear();
            menuDrawables.clear();
            window.close();
            exit(0);
            break;
            // Resize must be handled by menu functions because of unique text layout!

            // For unpausing the pause menu
        case sf::Event::KeyPressed:
            if (evnt.key.code == sf::Keyboard::Escape)
                isPause = !isPause;
        default:
            break;
        }
    }
}

/**
 * @brief Handles the input for the editor mode.
 *
 * This function checks for keyboard and mouse input in the editor mode and performs
 * corresponding actions based on the input. It allows the player to set the speed and
 * position of the player character, add and remove obstacles, and more.
 */
void handleEditorModeInput()
{
    // Input is discarded if window is not in focus
    if (!window.hasFocus())
        return;

    // Key bindings:
    // Space: places the player at current mouse cursor position
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Vector2f zeroSpeed(0.0f, 0.0f);
        player.setSpeed(zeroSpeed);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        player.setPosition(mousePosFloat);
    }
    // Z: zeroes player speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        sf::Vector2f zeroSpeed(0.0f, 0.0f);
        player.setSpeed(zeroSpeed);
    }
    // Left click:
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Get mouse position when click happens
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;
        // If LCtrl modifier key is pressed: places negative charge
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            // Create obstacle and add to level, push to drawables.
            std::shared_ptr<Obstacle> newObstacle(std::make_shared<Obstacle>(7.0f, -1500.0f, mousePos));
            level.addObstacle(newObstacle);

            gameDrawables.push_back(newObstacle->getBody());
        }
        // If LAlt modifier key is pressed: removes obstacles the mouse touches
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        {
            // Check for each obstacle if mouse is touching
            for (size_t i = 0; i < level.getObstacles().size(); i++)
            {
                // If touching, remove from obstacles and drawables
                if (level.getObstacles()[i]->getBody()->getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    level.removeObstacle(i);
                    gameDrawables.erase(gameDrawables.begin() + i + 1);
                }
            }
        }
    }
    // Right click: If LCtrl modifier key is pressed places positive charge
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        // Get mouse position when click happens
        sf::Vector2f mousePos;
        mousePos.x = sf::Mouse::getPosition(window).x;
        mousePos.y = sf::Mouse::getPosition(window).y;

        // Create obstacle and add to level, push to drawables.
        std::shared_ptr<Obstacle> newObstacle(std::make_shared<Obstacle>(7.0, 1500.0f, mousePos));
        level.addObstacle(newObstacle);
        gameDrawables.push_back(newObstacle->getBody());
    }
}

/**
 * @brief Renders the game window.
 *
 * This function clears the window, draws the game items, menu items, and editor overlay (if enabled),
 * and displays the window.
 */
void render()
{
    // Clear window
    window.clear(sf::Color::Black);

    // Draw game items
    for (const std::shared_ptr<sf::Drawable> &drawablePtr : gameDrawables)
        window.draw(*drawablePtr);

    // Draw menu items OVER game items
    for (const std::shared_ptr<sf::Drawable> &drawablePtr : menuDrawables)
        window.draw(*drawablePtr);

    // Draw editor overlay if editor mode is enabled
    if (isEditorMode)
    {
        sf::Text editorText;
        editorText.setFont(font);
        editorText.setCharacterSize(20);
        editorText.setFillColor(sf::Color::Magenta);
        editorText.setString("Editor Mode");
        editorText.setPosition(10, 10);
        window.draw(editorText);
    }

    window.display();
}

/**
 * @brief Sets the start speed of the player based on the user's input.
 *
 * This function allows the user to set the start speed of the player by clicking and dragging the mouse.
 * The player's start speed is calculated based on the distance and direction between the player's position and the mouse position.
 * The start speed is then used to determine the initial velocity of the player.
 */
void setStartSpeed()
{
    // Construct isMouseOnPlayer with the vector from if the vector from the mouse to the player is shorter than the radius of the player
    // To avoid calculating vectors, check if the x and y coordinates of the mouse is inside the circle
    bool isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getBody()->getPosition().x) < player.getCollisionRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getBody()->getPosition().y) < player.getCollisionRadius();

    // Wait for mouse click, when mouse is over player
    while (!(sf::Mouse::isButtonPressed((sf::Mouse::Left)) && isMouseOnPlayer) && window.isOpen())
    {
        // Handle events for allowing closing and pausing
        handleGameEvent();

        // Handle editor inputs if editor mode is enabled
        if (isEditorMode)
            handleEditorModeInput();

        render();

        // If paused dont calculate anything
        if (isPause)
            displayPauseOverlay();
        else
            isMouseOnPlayer = std::abs(sf::Mouse::getPosition(window).x - player.getBody()->getPosition().x) < player.getCollisionRadius() && std::abs(sf::Mouse::getPosition(window).y - player.getBody()->getPosition().y) < player.getCollisionRadius();
    }

    // If clicked on player initialize starting speed and create arrow rectangle
    sf::Vector2f startSpeed(0.0f, 0.0f);
    std::shared_ptr<sf::RectangleShape> arrow(std::make_shared<sf::RectangleShape>(sf::Vector2f(0.0f, arrowWidth)));
    arrow->setFillColor(sf::Color::Magenta);
    arrow->setOrigin(0.0f, arrowWidth / 2);
    gameDrawables.push_back(arrow);

    // Do until mouse is pressed (the player is dragging)
    while (sf::Mouse::isButtonPressed((sf::Mouse::Left)))
    {
        // Handle events
        handleGameEvent();
        if (isEditorMode)
            handleEditorModeInput();

        render();

        if (isPause)
            displayPauseOverlay();
        // If not paused draw arrow accordingly
        else
        {
            // Calculate the size the arrow needs to be by calculating the length of the vector stretching from the mouse to the player
            arrow->setPosition(player.getBody()->getPosition());
            arrow->setSize(sf::Vector2f(std::sqrt(startSpeed.x * startSpeed.x + startSpeed.y * startSpeed.y), arrowWidth));

            // Calculate rotation angle by calculating atan from the triangle the mouse and the player is drawing out and apply rotation
            float angle = std::atan2((sf::Mouse::getPosition(window).y - player.getBody()->getPosition().y), (sf::Mouse::getPosition(window).x - player.getBody()->getPosition().x)) * 180.0f / M_PI;
            arrow->setRotation(angle);

            // Set start speed by basically factoring by the length of the vector stretching between the player and mouse
            startSpeed.x = (player.getBody()->getPosition().x - sf::Mouse::getPosition(window).x);
            startSpeed.y = (player.getBody()->getPosition().y - sf::Mouse::getPosition(window).y);
            if (debug == 4)
                std::cout << "Start speed:\t" << std::sqrt(startSpeed.x * startSpeed.x + startSpeed.y * startSpeed.y)
                          << "\t\tx: " << startSpeed.x << "\ty: " << startSpeed.y << std::endl;
        }
    }

    // Remove arrow from drawables and set speed to calculated starting speed
    gameDrawables.pop_back();
    player.setSpeed(startSpeed);
}

// Run method with game loop
/**
 * @brief Runs the game loop.
 *
 * This function is responsible for running the main game loop. It updates the game state,
 * handles user input, and renders the game. The loop continues until the game window is closed.
 * If the window loses focus, the game is paused. If the game is in editor mode, it also handles
 * editor mode input. The player's physics is updated unless the game is paused.
 */
void runGame()
{
    // Restart game clock measuring deltaTime between iterations of simulation cycles
    gameClock.restart();

    // Game loop
    while (window.isOpen())
    {
        // If window loses focus, pause is requested
        if (!window.hasFocus())
            isPause = true;

        // If pause is requested, display pause overlay
        if (isPause)
            displayPauseOverlay();

        // Set deltaTime
        deltaTime = gameClock.restart().asSeconds();

        // Handle events
        handleGameEvent();

        // Handle editor inputs if editor mode is enabled
        if (isEditorMode)
            handleEditorModeInput();

        // Run iteration of physics simulation
        physics.updatePlayer();

        // Render drawables
        render();
    }
}

// Resets drawables, window and player
/**
 * @brief Starts the game.
 *
 * This function is responsible for initializing the game window, setting up the player's position,
 * clearing the drawables, and starting the game loop.
 */
void startGame()
{
    // Get previous window position to reopen the new window at the same position
    sf::Vector2i prevPosition = window.getPosition();
    window.close();
    // In editor mode resizing of the window is enabled
    if (isEditorMode)
        window.create(sf::VideoMode(level.getSize().x, level.getSize().y), "Charge game: " + level.getName() + " | EDITOR MODE", sf::Style::Default);
    else
        window.create(sf::VideoMode(level.getSize().x, level.getSize().y), "Charge game: " + level.getName(), sf::Style::Titlebar | sf::Style::Close);
    if (prevPosition.x != 0 && prevPosition.y != 0)
        window.setPosition(prevPosition);

    // Clear the window, set player's start position, clear drawables
    window.clear(sf::Color::Black);
    sf::Vector2f playerStartPos = level.getPlayerStartPos();
    player.setPosition(playerStartPos);
    gameDrawables.clear();
    menuDrawables.clear();
    // Player is first in drawables, then all obstacles are pushed
    gameDrawables.push_back(player.getBody());
    for (const std::shared_ptr<Obstacle> &obstacle : level.getObstacles())
    {
        gameDrawables.push_back(obstacle->getBody());
    }
    // Default is unpaused
    isPause = false;
    setStartSpeed();
    runGame();
}

/**
 * @brief Runs the main menu of the game.
 *
 * This function sets up and displays the main menu of the game. It creates and positions various menu items, handles user input, and updates the menu based on the user's actions.
 */
void runMainMenu()
{
    // Create game title text as shared pointer to allow being pushed to drawables.
    // This needs to be done because if something is pushed to a vector the address of the values themselves can change.
    // If the stored values are pointers, the value they point at remains constant in memory.
    std::shared_ptr<sf::Text> menuTitle = std::make_shared<sf::Text>(sf::Text("Charge game", font));
    menuTitle->setFillColor(sf::Color::Green);
    menuTitle->setCharacterSize(menuTitleSize);
    menuTitle->setOrigin(menuTitle->getLocalBounds().width / 2.0f, menuTitle->getLocalBounds().height / 2.0f);
    menuTitle->setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);
    menuDrawables.push_back(menuTitle);

    // Create delete level menu item
    std::shared_ptr<sf::Text> deleteLevelOption = std::make_shared<sf::Text>(sf::Text("Delete level", font));
    deleteLevelOption->setFillColor(sf::Color::Red);
    deleteLevelOption->setCharacterSize(20);
    deleteLevelOption->setOrigin(0.0f, deleteLevelOption->getLocalBounds().height);
    deleteLevelOption->setPosition(30.0f, window.getSize().y - 30.0f);
    menuDrawables.push_back(deleteLevelOption);

    // Create editor mode button
    std::shared_ptr<sf::Text> editorModeOption = std::make_shared<sf::Text>(sf::Text("Editor mode", font));
    editorModeOption->setFillColor(sf::Color::Magenta);
    editorModeOption->setCharacterSize(20);
    editorModeOption->setOrigin(editorModeOption->getLocalBounds().width, editorModeOption->getLocalBounds().height);
    editorModeOption->setPosition(window.getSize().x - 30.0f, window.getSize().y - 30.0f);
    menuDrawables.push_back(editorModeOption);

    // Create template of menu item
    // Menu items are also stored in a shared pointer vector because both menuDrawables and this menu reference them
    std::vector<std::shared_ptr<sf::Text>> menuItems;
    sf::Text menuItemTemplate("Empty Slot", font);
    menuItemTemplate.setCharacterSize(20);
    menuItemTemplate.setFillColor(sf::Color::White);

    // Get loadable level names
    const std::vector<std::string> &levels = LevelManager::getInstance()->getLoadables();

    // Create menu items for each level
    for (size_t i = 0; i < std::min(levels.size(), size_t(6)); i++)
    {
        std::shared_ptr<sf::Text> menuItem = std::make_shared<sf::Text>(menuItemTemplate);
        menuItem->setString(levels[i]);
        menuItem->setOrigin(menuItem->getGlobalBounds().width / 2.0f, menuItem->getGlobalBounds().height / 2.0f);
        menuItem->setPosition((windowWidth - 3 * 200) / 2.0f + 100 + (i % 3 * 200), windowHeight / 2.0f + (i / 3) * 50);
        menuItems.push_back(menuItem);
    }

    // Fill the rest of the grid with empty slots
    for (size_t i = levels.size(); i < 6; i++)
    {
        std::shared_ptr<sf::Text> menuItem = std::make_shared<sf::Text>(menuItemTemplate);
        menuItem->setOrigin(menuItem->getGlobalBounds().width / 2.0f, menuItem->getGlobalBounds().height / 2.0f);
        // Setup grid for levels
        menuItem->setPosition((windowWidth - 3 * 200) / 2.0f + 100 + (i % 3 * 200), windowHeight / 2.0f + (i / 3) * 50);
        menuItems.push_back(menuItem);
    }

    // Push every menu item to drawables
    for (const std::shared_ptr<sf::Text> &menuItem : menuItems)
    {
        menuDrawables.push_back(menuItem);
    }

    // Menu loop for
    bool isDeleteMode = false;
    while (window.isOpen())
    {
        render();
        if (debug == 6)
            for (size_t i = 0; i < menuItems.size(); i++)
            {
                std::cout << "Menu item " << i << ":\tx: " << menuItems[i]->getPosition().x << "\ty: " << menuItems[i]->getPosition().y << std::endl;
            }

        sf::Event evnt;
        // Polling for events (for menu item clicks and other resize and close events)
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
            {
                level.clearObstacles();
                gameDrawables.clear();
                menuDrawables.clear();
                window.close();
                exit(0);
            }
            else if (evnt.type == sf::Event::Resized)
            {
                // Reposition static texts
                resizeView(evnt);
                menuTitle->setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);
                deleteLevelOption->setPosition(30.0f, window.getSize().y - 30.0f);
                editorModeOption->setPosition(window.getSize().x - 30.0f, window.getSize().y - 30.0f);

                // Reposition each element in the grid
                for (size_t i = 0; i < menuItems.size(); i++)
                {
                    menuItems[i]->setPosition((window.getSize().x - 3 * 200) / 2.0f + 100 + (i % 3 * 200), window.getSize().y / 2.0f + (i / 3) * 50);
                }
            }
            else if (evnt.type != sf::Event::MouseButtonPressed)
                break;

            handleMenuEvent();
            render();

            // If mouse click event happened check for each level menu item if they have been clicked
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (size_t i = 0; i < menuItems.size(); i++)
            {
                if (menuItems[i].get()->getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    // If level menu item clicked and in delete mode, delete them
                    if (isDeleteMode)
                    {
                        // Delete the clicked level
                        // If default menu item was clicked do nothing
                        if (menuItems[i]->getString() != "Empty Slot")
                        {
                            // Setting the name to default
                            LevelManager::getInstance()->deleteLevel(menuItems[i]->getString());
                            menuItems[i]->setString("Empty Slot");

                            // Reposition the menu item
                            menuItems[i]->setOrigin(menuItems[i]->getGlobalBounds().width / 2.0f, menuItems[i]->getGlobalBounds().height / 2.0f);
                            menuItems[i]->setPosition((window.getSize().x - 3 * 200) / 2.0f + 100 + (i % 3 * 200), window.getSize().y / 2.0f + (i / 3) * 50);
                        }
                    }
                    // If not in delete mode load the clicked level
                    else
                    {
                        // If clicked level is default level load empty level
                        if (menuItems[i].get()->getString() == "Empty Slot")
                            level = Level();
                        else
                            level = LevelManager::getInstance()->loadLevel(levels[i]);

                        startGame();
                    }
                }
            }
            // Check is delete menu option was clicked
            if (deleteLevelOption->getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Flip delete mode
                isDeleteMode = !isDeleteMode;

                if (isDeleteMode)
                {
                    // Set all menu items name to red
                    for (std::shared_ptr<sf::Text> &menuItem : menuItems)
                        menuItem->setFillColor(sf::Color::Red);
                }
                else
                {
                    // Set all menu items name to default
                    for (std::shared_ptr<sf::Text> &menuItem : menuItems)
                        menuItem->setFillColor(sf::Color::White);
                }
            }

            // Check is editor mode menu item was clicked
            if (editorModeOption->getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                // Flip editor mode status
                isEditorMode = !isEditorMode;

                if (isEditorMode)
                {
                    // Set all menu items name to magenta
                    for (std::shared_ptr<sf::Text> &menuItem : menuItems)
                        menuItem->setFillColor(sf::Color::Magenta);
                }
                else
                {
                    // Set all menu items name to default
                    for (std::shared_ptr<sf::Text> &menuItem : menuItems)
                        menuItem->setFillColor(sf::Color::White);
                }
            }
        }
    }
}

/**
 * @brief Starts the main menu of the game.
 *
 * This function closes the current window, creates a new window for the main menu,
 * and sets the window position to the previous position if it was not (0,0).
 * It also clears the gameDrawables and menuDrawables vectors, sets the editor mode to false,
 * and calls the runMainMenu function.
 */
void startMainMenu()
{
    sf::Vector2i prevPosition = window.getPosition();
    window.close();
    window.create(sf::VideoMode(windowWidth, windowHeight), "Charge game: Main menu", sf::Style::Default);
    if (prevPosition.x != 0 && prevPosition.y != 0)
        window.setPosition(prevPosition);

    gameDrawables.clear();
    menuDrawables.clear();

    // Default is not in editor mode
    isEditorMode = false;
    runMainMenu();
}

/**
 * @brief Displays the pause overlay on the screen.
 *
 * This function clears the menuDrawables vector and adds various drawable objects to it, such as an overlay, text for "Paused",
 * text for "Back to main menu", and text for "Save level". It then enters a loop where it continuously renders the screen,
 * handles menu events, and checks for mouse clicks on the "Back to main menu" and "Save level" texts. If the "Back to main menu"
 * text is clicked, the menuDrawables vector is cleared and the startMainMenu function is called. If the "Save level" text is
 * clicked and the isEditorMode flag is true, the menuDrawables vector is cleared and the saveMenu function is called. The loop
 * continues until the window is closed or the isPause flag is false.
 */
void displayPauseOverlay()
{
    menuDrawables.clear();

    // Create semi-transparent black background rectangle as basis for overlay at the bottom
    std::shared_ptr<sf::RectangleShape> overlay(std::make_shared<sf::RectangleShape>(sf::Vector2f(window.getSize().x, window.getSize().y)));
    overlay->setFillColor(sf::Color(0, 0, 0, 191));
    menuDrawables.push_back(overlay);

    // Create "Paused" text at the top
    std::shared_ptr<sf::Text> pausedText(std::make_shared<sf::Text>("Paused", font, menuTitleSize));
    pausedText->setFillColor(sf::Color::White);
    pausedText->setOrigin(pausedText->getLocalBounds().width / 2.0f, pausedText->getLocalBounds().height / 2.0f);
    pausedText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);
    menuDrawables.push_back(pausedText);

    // Create back to main menu item
    std::shared_ptr<sf::Text> backToMenuText(std::make_shared<sf::Text>("Back to main menu", font, 20));
    backToMenuText->setFillColor(sf::Color::White);
    backToMenuText->setOrigin(backToMenuText->getLocalBounds().width / 2.0f, backToMenuText->getLocalBounds().height / 2.0f);
    backToMenuText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    menuDrawables.push_back(backToMenuText);

    // Create save level option, set it to fully white if editor mode is enabled (because saving only makes sense in that case)
    std::shared_ptr<sf::Text> saveText(std::make_shared<sf::Text>("Save level", font, 20));
    saveText->setFillColor(sf::Color(255, 255, 255, 100));
    if (isEditorMode)
        saveText->setFillColor(sf::Color::White);
    saveText->setOrigin(saveText->getLocalBounds().width / 2.0f, saveText->getLocalBounds().height / 2.0f);
    saveText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50.0f);
    menuDrawables.push_back(saveText);

    // Pause menu loop
    while (window.isOpen() && isPause)
    {
        render();
        handleMenuEvent();

        // If clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // If back to main menu item has been clicked wipe everything and return to the main menu
            if (backToMenuText->getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                menuDrawables.clear();
                startMainMenu();
            }
            // If in editor mode and save level option has been clicked open save menu
            if (isEditorMode && saveText->getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                menuDrawables.clear();
                saveMenu();
            }
        }
    }

    menuDrawables.clear();
}

/**
 * @brief Displays a save menu where the user can enter a level name and save the level.
 *
 * This function creates a save menu overlay with a text input field and a "Back" button.
 * The user can enter a level name using the keyboard and press Enter to save the level.
 * The function continuously renders the menu and handles user input until the level is saved or the window is closed.
 */
void saveMenu()
{
    // Create background overlay
    std::shared_ptr<sf::RectangleShape> overlay(std::make_shared<sf::RectangleShape>(sf::Vector2f(window.getSize().x, window.getSize().y)));
    overlay->setFillColor(sf::Color(0, 0, 0, 220));
    menuDrawables.push_back(overlay);

    // Create input text field

    // String for setting the input text field
    std::string levelName(level.getName());

    std::shared_ptr<sf::Text> inputText(std::make_shared<sf::Text>("Enter level name: " + levelName, font, 20));
    inputText->setFillColor(sf::Color::White);
    inputText->setOrigin(inputText->getLocalBounds().width / 2.0f, inputText->getLocalBounds().height / 2.0f);
    inputText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    menuDrawables.push_back(inputText);

    // Create back text
    std::shared_ptr<sf::Text> backText(std::make_shared<sf::Text>("Back", font, 20));
    backText->setFillColor(sf::Color::White);
    backText->setOrigin(backText->getLocalBounds().width / 2.0f, backText->getLocalBounds().height / 2.0f);
    backText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100.0f);
    menuDrawables.push_back(backText);

    // Boolean for checking if input is still to be expected
    bool isEnteringName = true;

    // Input loop
    while (window.isOpen() && isEnteringName)
    {
        render();

        sf::Event evnt;
        // Poll for events
        while (window.pollEvent(evnt))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            switch (evnt.type)
            {
            case sf::Event::Closed:
                level.clearObstacles();
                gameDrawables.clear();
                menuDrawables.clear();
                window.close();
                exit(0);
                break;
            case sf::Event::Resized:
                resizeView(evnt);
                inputText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
                backText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100.0f);
                break;
            case sf::Event::MouseButtonPressed:
                // If back button is clicked, return to pause menu
                if (backText->getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    menuDrawables.clear();
                    isEnteringName = false;
                }
                break;
            case sf::Event::KeyPressed:
                // If enter is pressed, the inputted string is set as level name and level is saved
                if (evnt.key.code == sf::Keyboard::Enter)
                {
                    // If entered level name is valid
                    if (level.setName(levelName))
                    {
                        // We can proceed with saving the level
                        isEnteringName = false;
                        level.setPlayerStartPos(player.getBody()->getPosition());
                        LevelManager::getInstance()->saveLevel(level);
                    }
                }
                // If backspace is pressed, delete the last character
                else if (evnt.key.code == sf::Keyboard::Backspace && !levelName.empty())
                {
                    levelName.pop_back();
                }
                // If a valid alphabet character is pressed
                else if (evnt.key.code <= sf::Keyboard::Z && levelName.size() <= levelNameCharLimit)
                {
                    // Parse the unicode input to ascii text (only a-z)
                    char inputChar = 'a' + evnt.key.code;

                    // Add inputted character to input string
                    levelName += inputChar;
                }

                // If text was entered, recenter whole textbox to the middle of the screen
                inputText->setOrigin(inputText->getLocalBounds().width / 2.0f, inputText->getLocalBounds().height / 2.0f);
                inputText->setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

                break;
            default:
                break;
            }
        }

        // Set displayed string to input string
        inputText->setString("Enter level name: " + levelName);
    }
    menuDrawables.clear();
    displayPauseOverlay();
}

/**
 * @brief The main entry point of the program.
 *
 * This function sets the framerate limit for the window, loads a font file, and starts the main menu.
 *
 * @return 0 indicating successful program execution.
 */
int main()
{
    // Sets framerate limit for window
    window.setFramerateLimit(targetFramerate);

    // Loads font
    if (!font.loadFromFile("fonts/joystix monospace.otf"))
        throw std::runtime_error("Couldn't locate font file!");

    // And starts main menu
    startMainMenu();

    return 0;
}