#pragma once
#include "Assets.hpp"
#include "Menu.hpp"
#include "Text.hpp"

class PauseMenu: public Menu
{
    bool active = false;
    Text pausedText;
    Text quitText;
    

  public:
    PauseMenu(int winWidth, int winHeight);
    ~PauseMenu();

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
    virtual void setActive(const bool _active) override;
};
