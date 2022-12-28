#pragma once
#include <memory>
#include <vector>

#include "Meteorite.hpp"
#include "Scene.hpp"

class WaveMngr
{
    static int m_current_wave;
    static int m_difficulty; // goes from 1 and up. it will scale the amout of enimies
    static int m_enimies_remaining;

  public:
    WaveMngr();
    static void constructWave(
        Scene& gameScene); // Constructs Enimies and adds them to the gamescene
    static void enemyKilled();
    static void passWave();
    static void getDifficulty();
    static void getWave();
};
