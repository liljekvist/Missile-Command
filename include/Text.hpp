#pragma once
#include "Assets.hpp"
#include "SceneObject.hpp"

class Text: public SceneObject
{
    sf::Text m_text;

  public:
    Text(const sf::Vector2f& position, const std::string& _text);
    Text(const sf::Vector2f& position, const std::string& _text, int fontSize);

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
