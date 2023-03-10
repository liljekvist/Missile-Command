#pragma once
#include "SceneObject.hpp"

class Projectile: public SceneObject
{
  public:
    Projectile(const sf::Vector2f& position);

    virtual auto getTarget() const -> sf::Vector2f = 0;

    auto update(const sf::Time& delta) -> bool override = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override = 0;
};