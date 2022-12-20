#pragma once
#include "SceneObject.hpp"

class Menu: public SceneObject
{
    Menu();
    virtual ~Menu();

    virtual bool update(const sf::Time& delta) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const = 0;
};
