#pragma once
#include "Button.hpp"
#include "SceneObject.hpp"
#include <optional>

class Menu: public SceneObject
{
    const sf::Vector2f m_position = sf::Vector2f(0, 0); // A menu always starts in 0,0

  public:
    Menu();

    auto update(const sf::Time& delta) -> bool override = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override = 0;
    virtual auto getClickedButton(
        const sf::Vector2i& mouse_position,
        const sf::RenderWindow& window) -> std::optional<Button> = 0;
};
