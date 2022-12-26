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
    float spriteTimer = 0.0f;
    int spriteIndex = 0;
    sf::Sprite metioriteSprite;
    sf::IntRect rectMetioriteSheet;
    bool destroyed = false;

  public:
    Metiorite(const sf::Vector2f& begin, const sf::Vector2f& target);
    ~Metiorite() override;

    sf::Vector2f getTarget() const;
    void destroy();

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
