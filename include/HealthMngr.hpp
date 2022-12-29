#pragma once
#include "SceneObject.hpp"
#include <SFML/Graphics/Sprite.hpp>

class HealthManager: public SceneObject
{
    int m_hearts = 0;

  public:
    HealthManager();

    auto getHearts() -> int;
    void addHeart();
    void loseHeart();
    void resetHearts();

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};