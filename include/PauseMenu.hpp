#pragma once
#include "Assets.hpp"
#include "Menu.hpp"

class PauseMenu: public Menu
{
    bool active = false;
    sf::Text pausedText;
    sf::Text quitText;

  public:
    PauseMenu(int winWidth, int winHeight);
    ~PauseMenu();

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
    virtual void setActive(const bool _active) override;
};
