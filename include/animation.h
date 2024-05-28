#pragma once

#include <SFML\Graphics.hpp>

#include "charge.h"

class Animation
{
protected:
    static std::shared_ptr<sf::Texture> playerTexture;  /**< The texture for the player animation. */
    static std::shared_ptr<sf::Texture> repulseTexture; /**< The texture for the repulsive obstacle animation. */
    static std::shared_ptr<sf::Texture> attractTexture; /**< The texture for the attractive obstacle animation. */
    static bool isLoaded;              /**< Whether the textures have been loaded. */

    std::shared_ptr<sf::Texture> texture; /**< The texture for this animation. */

public:
    enum class Type
    {
        RepulseObstacle,
        AttractObstacle,
        Player
    };

    const Type type; /**< The type of the animation. */

    /**
     * @brief Constructs an Animation object.
     */
    Animation(const Type type);

    /**
     * @brief Applies a transform to the animation.
     *
     * @param transform The transform to apply.
     */
    virtual void applyTransform(Charge &toTransform) const = 0;

    /**
     * @brief Gets the texture for this animation.
     *
     * @return The texture for this animation.
     */
    const sf::Texture *getTexture() const { return texture.get(); }
};
