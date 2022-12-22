#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <memory>
using std::shared_ptr, std::make_shared, std::unique_ptr, std::make_unique;
#include <any>
#include <map>
#include <random>

#include "Action.hpp"
#include "Assets.hpp"
#include "Explosion.hpp"
#include "FrameCounter.hpp"
#include "Meteorite.hpp"
#include "Missile.hpp"
#include "PauseMenu.hpp"
#include "Scene.hpp"
#include "State.hpp"
#include "Text.hpp"
#include "Tower.hpp"
#include "VectorMath.hpp"

class Game
{
    // Variables
    State::State gameState;
    int width;
    int height;
    sf::RenderWindow window; // Main game window
    sf::Clock clock;
    sf::Sprite backgroundSprite;
    Scene gameScene;
    Scene menuScene; // used for menus
    FrameCounter fCounter;
    std::multimap<Action::Action, std::any>
        inputBuffer; // A action and any associated data to that action. So if a shoot action is
                     // sent any will be a Vec2 with tthe mouse position. If a action cant be
                     // completed it will stay in the map to allow input buffering. Shoot actions
                     // may be discarded if all towers are on cooldown. otherwise tthe closest tower
                     // should shoot.
                     //
                     // I would like to make the input handling completly async so that even if the
                     // screen is not ready to draw a new frame the game still accepts input. Lets
                     // se if i have time to implement that :D PS. this is complete overkill but its
                     // fun so ill do it anyway

    // Functions
    void InitGame(); // Ruins once and inits windows and such
    void HandleInput(); // Handles input from user
    void UpdateGame(); // Updates, runs game logic and checks game state
    void UpdateScreen(); // Updates screen objects for drawing
    void ComposeFrame(); // Draws to the window

  public:
    Game(int _width, int _height);
    ~Game();
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    void GameLoop(); // Game Loop
};
