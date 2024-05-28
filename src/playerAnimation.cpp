#include <SFML\Graphics.hpp>

#include "playerAnimation.h"
#include "animation.h"

PlayerAnimation::PlayerAnimation() : Animation(Animation::Type::Player)
{
    texture = playerTexture;
}

void PlayerAnimation::applyTransform(Charge &toTransform) const
{
    toTransform.getBody()->rotate(0.1f);
}