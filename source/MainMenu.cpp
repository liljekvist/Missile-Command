#include "MainMenu.hpp"
#include "State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <string>

MainMenu::MainMenu()
    : m_game_name_text(sf::Vector2f(100, 100), "Main Menu", 48)
    , m_startButton(
          sf::Vector2f(100, 200),
          "Start game",
          []() -> State::State { return State::State::InGame; })
    , m_quitButton(sf::Vector2f(100, 300), "Quit", []() -> State::State {
        return State::State::Exit;
    }){};

auto MainMenu::update(const sf::Time& delta) -> bool
{
    return false;
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_game_name_text, states);
    target.draw(m_startButton, states);
    target.draw(m_quitButton, states);
}
auto MainMenu::getClickedButton(const sf::Vector2i& mouse_position, const sf::RenderWindow& window)
    -> std::optional<Button>
{
    if(m_startButton.isClicked(mouse_position, window))
    {
        return m_startButton;
    }
    if(m_quitButton.isClicked(mouse_position, window))
    {
        return m_quitButton;
    }
    return std::nullopt;
}
