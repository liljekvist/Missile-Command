#include "Game.hpp"
#include "GameHud.hpp"
#include <SFML/Window/Window.hpp>

GameHud::GameHud()
    : SceneObject(sf::Vector2f(0, 0))
    , m_score_text(sf::Vector2f(Game::width - 200, Game::height - (Game::BOTTOM_PADDING / 2)), "")
    , m_life_left_text(sf::Vector2f(10, Game::height - (Game::BOTTOM_PADDING / 2)), "")
    , m_current_wave_text(
          sf::Vector2f(Game::width / 2 - 45, Game::height - (Game::BOTTOM_PADDING / 2)),
          "")
{
}

void GameHud::setScoreText(const std::string& _text)
{
    m_score_text.updateText(_text);
}

void GameHud::setLifeText(const std::string& _text)
{
    m_life_left_text.updateText(_text);
}

void GameHud::setWaveText(const std::string& _text)
{
    m_current_wave_text.updateText(_text);
}

auto GameHud::update(const sf::Time& /*delta*/) -> bool
{
    return true;
}

void GameHud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_score_text, states);
    target.draw(m_life_left_text, states);
    target.draw(m_current_wave_text, states);
}
