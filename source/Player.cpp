#include "Player.hpp"
#include <SFML/Window/Window.hpp>
#include <memory>

Player::Player(): m_score(0), m_lifes_left(MAX_LIFES){};

void Player::initHud()
{
    m_hud = std::make_shared<GameHud>(); // Needs to be initialized after window and Game static
                                         // variables has been set.
    updateHud(); // Sets text to the right values
};

void Player::addScore(int score)
{
    m_score += score;
    updateHud();
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
    updateHud();
}

void Player::resetPlayer()
{
    m_lifes_left = MAX_LIFES;
    m_score = 0;
    updateHud();
}

void Player::updateHud()
{
    m_hud->setLifeText("Lifes: " + std::to_string(m_lifes_left));
    m_hud->setScoreText("Score: " + std::to_string(m_score));
}

auto Player::isAlive() const -> bool
{
    return (m_lifes_left > 0);
}

auto Player::getHud() -> std::shared_ptr<GameHud>
{
    return m_hud;
}
