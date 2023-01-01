#include "WaveMngr.hpp"
#include "Meteorite.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <memory>

int WaveMngr::m_current_wave = 0;
int WaveMngr::m_difficulty = 1; // goes from 0 and up. it will scale the amout of enimies
int WaveMngr::m_enimies_remaining = 0;

void WaveMngr::constructWave(Scene& gameScene)
{
    int inc = 0;
    do
    {
        gameScene.AddSceneObject(std::make_shared<Metiorite>(
            sf::Vector2f(rand() % Game::width, 0),
            sf::Vector2f(rand() % Game::width, Game::height - Game::BOTTOM_PADDING)));
        m_enimies_remaining++;
        inc++;
    } while((m_current_wave * m_difficulty) > inc);
}

void WaveMngr::enemyDestroyed()
{
    m_enimies_remaining--;
}

void WaveMngr::passWave()
{
    m_current_wave++;
}

auto WaveMngr::getDifficulty() -> int
{
    return m_difficulty;
}

auto WaveMngr::getWave() -> int
{
    return m_current_wave;
}

auto WaveMngr::getEnemiesRemaning() -> int
{
    return m_enimies_remaining;
}