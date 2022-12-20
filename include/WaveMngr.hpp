#pragma once
#include <memory>
using std::shared_ptr, std::make_shared, std::unique_ptr, std::make_unique;
#include <vector>

#include "Meteorite.hpp"
#include "Scene.hpp"

class WaveMngr
{
    int currentWave = 0;
    int difficulty = 1; // goes from 1 and up. it will scale the amout of enimies
    int enimiesRemaining = 0;

  public:
    void constructWave(Scene& gameScene); // Constructs Enimies and adds them to the gamescene
    void enemyKilled();
    void passWave();
    void getDifficulty();
    void getWave();
};
