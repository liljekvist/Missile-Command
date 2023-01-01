#include "Game.hpp"
#include "Action.hpp"
#include "PauseMenu.hpp"
#include "Player.hpp"
#include <SFML/System/Vector2.hpp>
#include <memory>

Game::Game(int _width, int _height)
    : m_gameState(State::Menu)
    , m_window(sf::VideoMode(_width, _height, 32), "Missile Command (gradius styled)")
{
    height = _height;
    width = _width;

    Assets::loadAssets(); // Need to load the background before making the sprite
    m_backgroundSprite = sf::Sprite(Assets::background);

    m_backgroundSprite.setScale(
        width / m_backgroundSprite.getLocalBounds().width,
        height / m_backgroundSprite.getLocalBounds().height);
    m_backgroundSprite.move(
        0,
        -30.0F); // Make a black bar at the bottom for text (That looks like gradius)
    m_player.initHud();
}

Game::~Game() = default;

void Game::InitGame()
{
    srand(time(nullptr)); // Set up the random number gen for use later in WaveMngr.

    m_window.setVerticalSyncEnabled(
        true); // no need to run the game at lightspeed. this game is a good usecase for vsync.

    m_gameScene.AddSceneObject(
        std::make_shared<Tower>(sf::Vector2f(width / 6.0F, height - BOTTOM_PADDING))); // Tower left
    m_gameScene.AddSceneObject(std::make_shared<Tower>(
        sf::Vector2f(width / 2.0F, height - BOTTOM_PADDING))); // Tower middle
    m_gameScene.AddSceneObject(std::make_shared<Tower>(
        sf::Vector2f(width - (width / 6.0F), height - BOTTOM_PADDING))); // Tower right

    m_gameScene.AddSceneObject(m_player.getHud());

    m_mmenu = std::make_shared<MainMenu>();
    m_mainMenuScene.AddSceneObject(m_mmenu);

    m_pmenu = std::make_shared<PauseMenu>();
    m_pauseMenuScene.AddSceneObject(m_pmenu);
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
                if(itr->first == Action::LMouse) // Action is shoot and any is mousePos
                {
                    if(auto button = m_pmenu->getClickedButton(
                           std::any_cast<sf::Vector2i>(itr->second),
                           m_window))
                    {
                        m_gameState = button->doAction();
                    }
                    itr = m_inputBuffer.erase(itr);
                }
                else
                {
                    itr++; // not handled event so ignore
                }
            }
            m_inputBuffer.clear(); // void inputs after handling is done
            break;
        case State::Menu:
            for(auto itr = m_inputBuffer.begin(); itr != m_inputBuffer.end();) // ACtions
            {
                if(itr->first == Action::LMouse) // Action is shoot and any is mousePos
                {
                    if(auto button = m_mmenu->getClickedButton(
                           std::any_cast<sf::Vector2i>(itr->second),
                           m_window))
                    {
                        m_gameState = button->doAction();
                    }
                    itr = m_inputBuffer.erase(itr);
                }
                else
                {
                    itr++; // not handled event so ignore
                }
            }
            m_inputBuffer.clear(); // void inputs after handling is done
            break;
        case State::Exit: break;
    }
}

void Game::UpdateScreen() // Needs a refactor too complex. maybe split it into parts or move code to
                          // objects
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
                        int metiorites_destroyed =
                            0; // this is used for if a player destroys multiple metiorites with one
                               // missile the score will multiply with the amout destroyed
                        std::for_each(
                            metiorites.begin(),
                            metiorites.end(),
                            [&position, &metiorites_destroyed, this](auto& elem) {
                                if(elem->isInsideRadiusOfPos(position, EXPLOTION_RADIUS))
                                {
                                    metiorites_destroyed++;
                                    m_player.addScore(SCORE_PER_METIORITE * metiorites_destroyed);
                                    elem->destroy();
                                }
                            });
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

                        if(p_metiorite->hasReachedTarget())
                        {
                            m_player.removeLife();
                        }

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

        case State::GameOver: break;
        case State::Pause: break;
        case State::Menu: break;
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
            for(auto& itr : m_pauseMenuScene)
            {
                m_window.draw(*itr);
            }
            break;
        case State::Menu:
            for(auto& itr : m_mainMenuScene)
            {
                m_window.draw(*itr);
            }
            break;
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
