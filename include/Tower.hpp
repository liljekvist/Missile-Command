#pragma once
#include "SceneObject.hpp"

class Tower: public SceneObject
{
  public:
    virtual bool update(const sf::Time& delta);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const;
};
