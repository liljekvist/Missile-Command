#pragma once
#include "Assets.hpp"
#include "Menu.hpp"
#include "Text.hpp"

class PauseMenu: public Menu
{
    bool m_active = false;
    Text m_pausedText;
    Text m_quitText;

  public:
    PauseMenu(int winWidth, int winHeight);

    auto update(const sf::Time& delta) -> bool override;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        const override;
    void setActive(bool _active) override;
};
