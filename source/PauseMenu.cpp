#include "PauseMenu.hpp"
#include <SFML/System/Vector2.hpp>

PauseMenu::PauseMenu(int winWidth, int winHeight)
    : Menu()
    , pausedText(sf::Vector2f(winWidth / 2.0f, 100), "Paused", 48)
    , quitText(sf::Vector2f(winWidth / 2.0f, 200), "Quit"){};

PauseMenu::~PauseMenu() {}

bool PauseMenu::update(const sf::Time& delta)
{
    return false;
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(active)
    {
        target.draw(pausedText, states);
        target.draw(quitText, states);
    }
}

void PauseMenu::setActive(const bool _active)
{
    active = _active;
}
