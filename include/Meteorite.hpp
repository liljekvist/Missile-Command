#pragma once

#include "Assets.hpp"
#include "Projectile.hpp"
#include "SceneObject.hpp"
#include "VectorMath.hpp"

class Metiorite: public Projectile
{
    // Magic constants
    static constexpr float SPRITE_SCALE_FACTOR = 0.5F;
    static constexpr float ANIMATION_ROTATION_DELAY = 0.17F;
    static constexpr float MOVE_SPEED = 80.0F;
    static constexpr int SPRITES_PER_SHEET = 3;

    // Variables
    sf::Vector2f m_begin;
    sf::Vector2f m_target;
    sf::Vector2f m_direction;
    float m_spriteTimer = 0.0F;
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
