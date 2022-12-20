#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "SceneObject.hpp"
#include "Assets.hpp"

class Explosion: public SceneObject
{
    float m_radius;
    float m_targetRadius;
    float spriteTimer = 0.0f;
    int spriteIndex = 0;
    sf::Sprite explotionSheet;
    sf::IntRect rectExplotionSheet;

  public:
    Explosion(const sf::Vector2f& position, float radius);
    ~Explosion() override;

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};

#endif
