#include "Player.hpp"
#include <SFML/Window/Window.hpp>
#include <memory>

Player::Player(): m_score(0), m_lifes_left(MAX_LIFES)
{
    m_hud = std::make_shared<GameHud>();
};

void Player::addScore(int score)
{
    m_score += score;
}

void Player::removeLife()
{
    if(m_lifes_left <= 0)
    {
        m_dead = true;
    }
    else
    {
        m_lifes_left--;
    }
}

void Player::resetPlayer()
{
    m_lifes_left = MAX_LIFES;
    m_score = 0;
}

void Player::updateHud()
{
    m_hud->setLifeText("Lifes: " + std::to_string(m_lifes_left));
    m_hud->setScoreText("Score: " + std::to_string(m_score));
}

auto Player::getHud() -> std::shared_ptr<GameHud>
{
    return m_hud;
}
