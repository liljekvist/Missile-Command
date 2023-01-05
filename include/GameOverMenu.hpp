#pragma once
#include "Assets.hpp"
#include "Button.hpp"
#include "Menu.hpp"
#include "State.hpp"
#include "Text.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

class GameOverMenu: public Menu
{
    Text m_pausedText;
    Button m_quitButton;

  public:
    GameOverMenu();

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
    auto getClickedButton(const sf::Vector2i& mouse_position, const sf::RenderWindow& window)
        -> std::optional<Button> override;
};
