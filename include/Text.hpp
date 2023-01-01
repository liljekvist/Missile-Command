#pragma once
#include "Assets.hpp"
#include "SceneObject.hpp"

class Text: public SceneObject
{
    static constexpr int DEFAULT_FONTSIZE = 24;

    sf::Text m_text;

  public:
    Text(const sf::Vector2f& position, const std::string& _text, int fontSize = DEFAULT_FONTSIZE);

    void updateText(const std::string& _text);

    auto getRawTextObject() -> sf::Text&;

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
