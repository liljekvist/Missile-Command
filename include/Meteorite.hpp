#pragma once

#include "Assets.hpp"
#include "Projectile.hpp"
#include "SceneObject.hpp"
#include "VectorMath.hpp"

class Metiorite: public Projectile
{
    sf::Vector2f m_begin;
    sf::Vector2f m_target;
    sf::Vector2f m_direction;
    float m_spriteTimer = 0.0f;
    int m_spriteIndex = 0;
    sf::Sprite m_metioriteSprite;
    sf::IntRect m_rectMetioriteSheet;
    bool m_destroyed = false;

  public:
    Metiorite(const sf::Vector2f& begin, const sf::Vector2f& target);

    auto getTarget() const -> sf::Vector2f;
    void destroy();

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
