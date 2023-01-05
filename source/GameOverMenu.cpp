#include "GameOverMenu.hpp"

GameOverMenu::GameOverMenu()
    : m_pausedText(sf::Vector2f(100, 100), "Game Over", 48)
    , m_quitButton(sf::Vector2f(100, 200), "Quit", []() -> State::State {
        return State::State::Menu;
    }){};

auto GameOverMenu::update(const sf::Time& delta) -> bool
{
    return true;
}

void GameOverMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_pausedText, states);
    target.draw(m_quitButton, states);
}

auto GameOverMenu::getClickedButton(
    const sf::Vector2i& mouse_position,
    const sf::RenderWindow& window) -> std::optional<Button>
{
    if(m_quitButton.isClicked(mouse_position, window))
    {
        return m_quitButton;
    }
    return std::nullopt;
}
