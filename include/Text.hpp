#pragma once
#include "Assets.hpp"
#include "SceneObject.hpp"

class Text: public SceneObject
{
    sf::Text text;

  public:
    Text(const sf::Vector2f& position, std::string text);
    ~Text() override;

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
