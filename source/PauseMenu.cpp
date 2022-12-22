#include "PauseMenu.hpp"

PauseMenu::PauseMenu(int winWidth, int winHeight): Menu()
{
    pausedText.setFont(Assets::textFont);
    pausedText.setString("Paused");
    pausedText.setCharacterSize(48);
    pausedText.setFillColor(sf::Color::White);
    pausedText.setPosition(
        winWidth - (pausedText.getLocalBounds().width / 2),
        winHeight + (pausedText.getLocalBounds().height / 2));
    pausedText.setStyle(sf::Text::Bold);
};

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
    }
}

void PauseMenu::setActive(const bool _active)
{
    active = _active;
}
