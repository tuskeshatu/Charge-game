#include <SFML\Graphics.hpp>

#include "animation.h"

std::shared_ptr<sf::Texture> Animation::playerTexture;
std::shared_ptr<sf::Texture> Animation::repulseTexture;
std::shared_ptr<sf::Texture> Animation::attractTexture;
bool Animation::isLoaded = false;

// Constructs an Animation object.
// Loads the textures for the player, repulse obstacle, and attract obstacle if they have not been loaded.
Animation::Animation(const Type type) : type(type)
{
    if (!isLoaded)
    {
        playerTexture = std::make_shared<sf::Texture>();
        repulseTexture = std::make_shared<sf::Texture>();
        attractTexture = std::make_shared<sf::Texture>();
        if (!playerTexture->loadFromFile("resources/textures/player_texture.png"))
        {
            throw std::runtime_error("Failed to load player texture.");
        }
        if (!repulseTexture->loadFromFile("resources/textures/repulse_obstacle_texture.png"))
        {
            throw std::runtime_error("Failed to load repulse texture.");
        }
        if (!attractTexture->loadFromFile("resources/textures/attract_obstacle_texture.png"))
        {
            throw std::runtime_error("Failed to load attract texture.");
        }
         playerTexture->setSmooth(true);
         repulseTexture->setSmooth(true);
         attractTexture->setSmooth(true);
        isLoaded = true;
    }
}