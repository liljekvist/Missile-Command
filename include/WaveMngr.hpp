#pragma once
#include <memory>
#include <vector>

#include "Game.hpp"
#include "Meteorite.hpp"
#include "Scene.hpp"

class WaveMngr
{
    static int m_current_wave; // Rechable everywhere but private in my eyes ;´()
    static int m_difficulty;
    static int m_enimies_remaining;

  public:
    static void constructWave(
        Scene& gameScene); // Constructs Enimies and adds them to the gamescene
    static void enemyDestroyed();
    static void passWave();
    static auto getDifficulty() -> int;
    static auto getWave() -> int;
    static auto getEnemiesRemaning() -> int;
    static void reset();
};
