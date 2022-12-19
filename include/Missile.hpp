#pragma once

#include "Line.hpp"
#include "Projectile.hpp"
#include "Textures.hpp"

class Missile
    : public Projectile
    , public SceneObject
{
    sf::Vector2f m_begin;
    sf::Vector2f m_target;
    sf::Vector2f m_direction;
    sf::Sprite m_rocketShape;

  public:
    Missile(const sf::Vector2f& begin, const sf::Vector2f& target);
    ~Missile() override;

    sf::Vector2f getTarget() const;

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
