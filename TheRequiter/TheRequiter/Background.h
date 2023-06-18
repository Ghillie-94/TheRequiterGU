#pragma once
#include "SpriteObject.h"
#include <SFML/Graphics.hpp>


class Background
{
public:
    Background();

    void Draw(sf::RenderTarget& target);


protected:
    sf::Sprite background;
};

