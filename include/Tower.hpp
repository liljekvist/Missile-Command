#pragma once

#include "SceneObject.hpp"
#include "VectorMath.hpp"

class Tower: public SceneObject
{
    sf::Texture texTower;
    sf::Sprite sprTower;
    sf::Vector2f m_direction;

  public:
    Tower(sf::Vector2f pos);
    ~Tower();
    virtual bool update(const sf::Time& delta);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const;
};
