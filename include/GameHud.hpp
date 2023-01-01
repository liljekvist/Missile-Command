#pragma once

#include "SceneObject.hpp"
#include "Text.hpp"
#include <SFML/System/Vector2.hpp>

class GameHud: public SceneObject
{
    Text m_score_text;
    Text m_life_left_text;

  public:
    GameHud();

    void setScoreText(const std::string& _text);
    void setLifeText(const std::string& _text);

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};