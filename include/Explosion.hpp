#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Assets.hpp"
#include "SceneObject.hpp"

class Explosion: public SceneObject
{
    float m_radius;
    float m_targetRadius;
    float m_spriteTimer = 0.0F;
    int m_spriteIndex = 0;
    sf::Sprite m_explotionSheet;
    sf::IntRect m_rectExplotionSheet;

  public:
    Explosion(const sf::Vector2f& position, float radius);

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};

#endif
