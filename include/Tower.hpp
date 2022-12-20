#pragma once

#include "SceneObject.hpp"
#include "Assets.hpp"
#include "VectorMath.hpp"

class Tower: public SceneObject
{
    const float cooldownPeriod = 1.0f; // Tower cooldown period
    sf::Sprite sprTower;
    sf::Vector2f m_direction;
    sf::Clock towerClock;
    sf::Time lastFire;
    bool onCooldown = false;

  public:
    Tower(sf::Vector2f pos);
    ~Tower();
    void fireMissile();
    bool canFireMissile();
    virtual bool update(const sf::Time& delta);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const;
};
