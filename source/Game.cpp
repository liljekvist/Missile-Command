#include "Game.hpp"
#include "Action.hpp"
#include "State.hpp"
#include "VectorMath.hpp"
#include "WaveMngr.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>

Game::Game(int width, int height)
    : m_gameState(State::InGame)
    , m_window(sf::VideoMode(width, height, 32), "Missile Command")
{
    Game::height = height;
    Game::width = width;
    Assets::loadAssets(); // Need to load the background before making the sprite
    m_backgroundSprite = sf::Sprite(Assets::background);

    m_backgroundSprite.setScale(
        width / m_backgroundSprite.getLocalBounds().width,
        height / m_backgroundSprite.getLocalBounds().height);
}

Game::~Game() = default;

void Game::InitGame()
{
    srand(time(nullptr)); // Set up the random number gen for use later in WaveMngr.

    m_window.setVerticalSyncEnabled(
        true); // no need to run the game at lightspeed. this game is a good usecase for vsync.

    m_gameScene.AddSceneObject(
        std::make_shared<Tower>(sf::Vector2f(width / 6.0F, height - 50))); // Tower left
    m_gameScene.AddSceneObject(
        std::make_shared<Tower>(sf::Vector2f(width / 2.0F, height - 50))); // Tower middle
    m_gameScene.AddSceneObject(
        std::make_shared<Tower>(sf::Vector2f(width - (width / 6.0F), height - 50))); // Tower right

    m_menuScene.AddSceneObject(std::make_shared<PauseMenu>(width, height));
}

void Game::HandleInput()
{
    sf::Event event{};
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                m_gameState = (m_gameState == State::InGame) ? State::Pause : State::InGame;
            }
            if(event.key.code == sf::Keyboard::Space)
            {
                m_inputBuffer.insert(std::pair(Action::Space, nullptr));
            }
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                m_inputBuffer.insert(std::pair(Action::LMouse, sf::Mouse::getPosition(m_window)));
            }
        }
    }
}

void Game::UpdateGame()
{
    switch(m_gameState)
    {
        case State::State::InGame:
            for(auto itr = m_inputBuffer.begin(); itr != m_inputBuffer.end();) // ACtions
            {
                if(itr->first == Action::LMouse) // Action is shoot and any is mousePos
                {
                    auto mouse_position = vec2iToVec2f(std::any_cast<sf::Vector2i>(itr->second));
                    auto closest_tower_ptr = m_gameScene.GetClosestFirableTower(mouse_position);
                    if(closest_tower_ptr != nullptr)
                    {
                        closest_tower_ptr->fireMissile();
                        m_gameScene.AddSceneObject(std::make_shared<Missile>(
                            closest_tower_ptr->getPosition(),
                            mouse_position));
                    }

                    itr = m_inputBuffer.erase(itr);
                }
                else
                {
                    itr++; // not handled event so ignore
                }
            }
            // Wave Logic
            if(WaveMngr::getEnemiesRemaning() == 0)
            {
                WaveMngr::passWave(); // Passing last wave.
                WaveMngr::constructWave(m_gameScene);
            }
            break;
        case State::State::Pause:
            for(auto itr = m_inputBuffer.begin(); itr != m_inputBuffer.end();) // ACtions
            {
                if(itr->first == Action::Space) // Action is shoot and any is mousePos
                {
                    m_gameState = State::State::Exit;

                    itr = m_inputBuffer.erase(itr);
                }
                else
                {
                    itr++; // not handled event so ignore
                }
            }
            m_inputBuffer.clear(); // void inputs after handling is done
            break;
        case State::Menu: break;
        case State::Exit: break;
    }
}

void Game::UpdateScreen() // Needs a refactor
{
    sf::Time delta = m_clock.restart();

    switch(m_gameState)
    {
        case State::State::InGame:
            std::cout << m_gameScene.getSize() << std::endl;
            for(const auto& obj : m_gameScene.getVec())
            {
                if(!obj->update(delta))
                {
                    if(std::shared_ptr<Missile> p_missile = std::dynamic_pointer_cast<Missile>(obj);
                       p_missile)
                    {
                        sf::Vector2f position = p_missile->getPosition();
                        auto metiorites = m_gameScene.getAllOfType<Metiorite>();
                        for(const auto& metiorite : metiorites)
                        {
                            if(distanceBetween(position, metiorite->getPosition())
                               < EXPLOTION_RADIUS)
                            {
                                metiorite->destroy();
                            }
                        }
                        m_gameScene.ReleaseSceneObject(obj);
                        m_gameScene.AddSceneObject(
                            std::make_unique<Explosion>(position, EXPLOTION_RADIUS));
                    }
                    else if(std::shared_ptr<Metiorite> p_metiorite =
                                std::dynamic_pointer_cast<Metiorite>(obj);
                            p_metiorite)
                    {
                        sf::Vector2f position = p_metiorite->getPosition();
                        m_gameScene.ReleaseSceneObject(obj);
                        WaveMngr::enemyDestroyed();
                        m_gameScene.AddSceneObject(
                            std::make_unique<Explosion>(position, EXPLOTION_RADIUS));
                    }
                    else if(std::shared_ptr<Explosion> p_explotion =
                                std::dynamic_pointer_cast<Explosion>(obj);
                            p_explotion)
                    {
                        m_gameScene.ReleaseSceneObject(obj);
                    }
                }
            }
            break;
        case State::State::Pause:
            for(const auto& obj : m_menuScene.getVec())
            {
                if(!obj->update(delta))
                {
                    if(std::shared_ptr<PauseMenu> pmenu = std::dynamic_pointer_cast<PauseMenu>(obj);
                       pmenu)
                    {
                        pmenu->setActive(true);
                    }
                    // l�gg till mainmenu och scoreboard
                }
            }
            break;
        case State::State::Menu:
            for(const auto& obj : m_menuScene.getVec())
            {
                if(!obj->update(delta))
                {
                    if(std::shared_ptr<PauseMenu> p_menu =
                           std::dynamic_pointer_cast<PauseMenu>(obj);
                       p_menu)
                    {
                        p_menu->setActive(false);
                    }
                    // l�gg till mainmenu och scoreboard
                }
            }
            break;
        case State::Exit: break;
    }
}

void Game::ComposeFrame()
{
    // Drawing
    m_window.clear();
    switch(m_gameState)
    {
        case State::State::InGame:
            m_window.draw(m_backgroundSprite);
            for(auto& itr : m_gameScene)
            {
                m_window.draw(*itr);
            }
            break;
        case State::State::Pause:
            for(auto& itr : m_menuScene)
            {
                m_window.draw(*itr);
            }
            break;
        case State::Menu: break;
        case State::Exit: break;
    }

    m_window.display();
    // fCounter.updateFps();
    // fCounter.printFps();
}

void Game::GameLoop()
{
    InitGame();

    while(m_gameState != State::Exit && m_window.isOpen())
    {
        HandleInput();
        UpdateGame();
        UpdateScreen();
        ComposeFrame();
    }

    m_window.close();
}
