#pragma once
#include "Menu.hpp"

class PauseMenu: public Menu
{
    PauseMenu();
    ~PauseMenu();

    bool update(const sf::Time& delta) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
};
