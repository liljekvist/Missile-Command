#include "PauseMenu.hpp"
#include "State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

PauseMenu::PauseMenu()
    : m_pausedText(sf::Vector2f(100, 100), "Paused", 48)
    , m_quitButton(sf::Vector2f(100, 200), "Quit", []() -> State::State {
        return State::State::Exit;
    }){};

auto PauseMenu::update(const sf::Time& delta) -> bool
{
    return true;
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_pausedText, states);
    target.draw(m_quitButton, states);
}

auto PauseMenu::getClickedButton(const sf::Vector2i& mouse_position, const sf::RenderWindow& window)
    -> std::optional<Button>
{
    if(m_quitButton.isClicked(mouse_position, window))
    {
        return m_quitButton;
    }
    return std::nullopt;
}
