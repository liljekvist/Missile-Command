#include "PauseMenu.hpp"
#include <SFML/System/Vector2.hpp>

PauseMenu::PauseMenu(int winWidth, int winHeight)
    : m_pausedText(sf::Vector2f(winWidth / 2.0f, 100), "Paused", 48)
    , m_quitText(sf::Vector2f(winWidth / 2.0f, 200), "Quit"){};

auto PauseMenu::update(const sf::Time& delta) -> bool
{
    return false;
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_active)
    {
        target.draw(m_pausedText, states);
        target.draw(m_quitText, states);
    }
}

void PauseMenu::setActive(const bool _active)
{
    m_active = _active;
}
