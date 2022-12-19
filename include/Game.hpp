#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <memory>
using std::shared_ptr, std::make_shared, std::unique_ptr, std::make_unique;
#include <random>

#include "Explosion.hpp"
#include "FrameCounter.hpp"
#include "Missile.hpp"
#include "Scene.hpp"
#include "Tower.hpp"

class Game
{
    // Variables
    int width;
    int height;
    sf::RenderWindow window; // Main game window
    sf::Clock clock;
    Scene sDrawables;
    bool running = true;
    FrameCounter fCounter;

    // Functions
    void InitGame(); // Ruins once and inits windows and such
    void HandleInput(); // Handles input from user
    void UpdateGame(); // Updates and runs game logic
    void DrawGame(); // Draws to the window

  public:
    Game();
    Game(int _width, int _height);
    ~Game();
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    void GameLoop(); // Game Loop
};
