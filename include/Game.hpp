#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <any>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <random>

#include "Action.hpp"
#include "Assets.hpp"
#include "Explosion.hpp"
#include "FrameCounter.hpp"
#include "GameHud.hpp"
#include "GameOverMenu.hpp"
#include "MainMenu.hpp"
#include "Meteorite.hpp"
#include "Missile.hpp"
#include "PauseMenu.hpp"
#include "Player.hpp"
#include "Scene.hpp"
#include "State.hpp"
#include "Text.hpp"
#include "Tower.hpp"
#include "VectorMath.hpp"
#include "WaveMngr.hpp"

class Game
{
    // Game Config constants
    static constexpr float EXPLOTION_RADIUS = 60.F;
    static constexpr int SCORE_PER_METIORITE = 1000;

    // Variables
    State::State m_gameState;
    sf::RenderWindow m_window; // Main game window
    sf::Clock m_clock;
    sf::Sprite m_backgroundSprite;
    Scene m_gameScene;
    Scene m_pauseMenuScene;
    Scene m_mainMenuScene;
    Scene m_gameOverScene;
    Player m_player;
    std::shared_ptr<PauseMenu> m_pmenu;
    std::shared_ptr<MainMenu> m_mmenu;
    std::shared_ptr<GameOverMenu> m_omenu;
    std::multimap<Action::Action, std::any>
        m_inputBuffer; // A action and any associated data to that action. So if a shoot action is
                       // sent any will be a Vec2 with tthe mouse position. If a action cant be
                       // completed it will stay in the map to allow input buffering. Shoot actions
                       // may be discarded if all towers are on cooldown. otherwise tthe closest
                       // tower should shoot.
                       //
                       // I would like to make the input handling completly async so that even if
                       // the screen is not ready to draw a new frame the game still accepts input.
                       // Lets se if i have time to implement that :D PS. this is complete overkill
                       // but its fun so ill do it anyway

    // Functions
    void InitGame(); // Ruins once and inits windows and such
    void HandleInput(); // Handles input from user
    void UpdateGame(); // Updates, runs game logic and checks game state
    void UpdateScreen(); // Updates screen objects for drawing
    void ComposeFrame(); // Draws to the window

  protected:
  public:
    static constexpr float BOTTOM_PADDING = 70.F;
    inline static int width;
    inline static int height;

    Game(int width, int height);
    ~Game();
    Game(const Game& other) = delete;
    Game(Game&& other) = delete;
    auto operator=(Game&& rhs) -> Game& = delete;
    auto operator=(const Game& other) -> Game& = delete;
    void GameLoop(); // Game Loop
};
