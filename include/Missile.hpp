#pragma once

#include "Line.hpp"
#include "Projectile.hpp"

class Missile
    : public Projectile
    , public SceneObject
{
    sf::Vector2f m_begin;
    sf::Vector2f m_target;
    sf::Vector2f m_direction;

    // Triangles don't exist in SFML. But if you think about it, a triangle is
    // just a "circle" with three points...
    sf::CircleShape m_rocketShape;
    Line m_trail;

  public:
    Missile(const sf::Vector2f& begin, const sf::Vector2f& target);
    ~Missile() override;

    sf::Vector2f getTarget() const;

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
