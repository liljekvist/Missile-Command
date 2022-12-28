#pragma once

#include "Assets.hpp"
#include "SceneObject.hpp"
#include "VectorMath.hpp"

class Tower: public SceneObject
{
    static constexpr float COOLDOWN_PERIOD = 1.0F; // Tower cooldown period
    sf::Sprite m_sprTower;
    sf::Vector2f m_direction;
    sf::Clock m_towerClock;
    sf::Time m_lastFire;
    bool m_onCooldown = false;

  public:
    Tower(sf::Vector2f pos);
    void fireMissile();
    auto canFireMissile() const -> bool;
    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
