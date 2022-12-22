#pragma once
#include "SceneObject.hpp"

class Menu: public SceneObject
{
    const sf::Vector2f position = sf::Vector2f(0, 0); // A menu always starts in 0,0

  public:
    Menu();
    virtual ~Menu();

    virtual bool update(const sf::Time& delta) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const = 0;
    virtual void setActive(const bool _active) = 0;
};
