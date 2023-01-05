#pragma once

#include "GameHud.hpp"
#include "SceneObject.hpp"
#include <SFML/Window/Window.hpp>
#include <memory>
#include <string>

class Player
{
    static constexpr int MAX_LIFES = 3;

    std::shared_ptr<GameHud>
        m_hud; // will push this onto scene later. since its a shared pointer it *should* be fine.

    int m_score;
    int m_lifes_left;
    bool m_dead = false;

  public:
    Player();

    void initHud();
    void addScore(int score);
    void removeLife();
    void resetPlayer();
    void updateHud();
    [[nodiscard]] auto isAlive() const -> bool;
    auto getHud() -> std::shared_ptr<GameHud>;
};
