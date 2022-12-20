#pragma once
#include "SceneObject.hpp"

class Projectile: public SceneObject
{
  public:
    Projectile(const sf::Vector2f& position);
    virtual ~Projectile();

    virtual bool update(const sf::Time& delta) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const = 0;
};
