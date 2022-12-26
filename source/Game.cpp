#include "Game.hpp"
#include <iostream>

Game::Game(int _width, int _height)
    : width(_width)
    , height(_height)
    , window(sf::VideoMode(width, height, 32), "Missile Command")
{
    gameState = State::InGame;
    Assets::loadAssets(); // Need to load the background before making the sprite
    backgroundSprite = sf::Sprite(Assets::background);

    backgroundSprite.setScale(
        width / backgroundSprite.getLocalBounds().width,
        height / backgroundSprite.getLocalBounds().height);
}

Game::~Game() {}

void Game::InitGame()
{
    gameScene.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width / 6.0f, height - 50))); // Tower left
    gameScene.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width / 2.0f, height - 50))); // Tower middle
    gameScene.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width - (width / 6.0f), height - 50))); // Tower right
    menuScene.AddSceneObject(make_shared<PauseMenu>(width, height));
}

void Game::HandleInput()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
                gameState = (gameState == State::InGame) ? State::Pause : State::InGame;
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
                inputBuffer.insert(std::pair(Action::LMouse, sf::Mouse::getPosition(window)));
        }
    }
}

void Game::UpdateGame()
{
    switch(gameState)
    {
        case State::State::InGame:
            for(auto itr = inputBuffer.begin(); itr != inputBuffer.end();) // ACtions
            {
                if(itr->first == Action::LMouse) // Action is shoot and any is mousePos
                {
                    auto mousePosition = vec2iToVec2f(std::any_cast<sf::Vector2i>(itr->second));
                    auto closestTowerPtr = gameScene.GetClosestFirableTower(mousePosition);
                    if(closestTowerPtr != nullptr)
                    {
                        closestTowerPtr->fireMissile();
                        gameScene.AddSceneObject(
                            make_shared<Missile>(closestTowerPtr->getPosition(), mousePosition));
                    }

                    itr = inputBuffer.erase(itr);
                }
                else
                    itr++; // not handled event so ignore
            }
            break;
        case State::State::Pause:
            inputBuffer.clear(); // void inputs since game is paused
            break;
        case State::Menu: break;
        case State::Exit: break;
    }
}

void Game::UpdateScreen()
{
    sf::Time delta = clock.restart();

    switch(gameState)
    {
        case State::State::InGame:
            for(auto obj : gameScene.getVec())
            {
                if(!obj->update(delta))
                {
                    if(shared_ptr<Missile> pMissile = std::dynamic_pointer_cast<Missile>(obj);
                       pMissile)
                    {
                        sf::Vector2f position = pMissile->getTarget();
                        gameScene.ReleaseSceneObject(obj);
                        gameScene.AddSceneObject(make_unique<Explosion>(position, 20.f));
                    }
                    else if(shared_ptr<Metiorite> pMetiorite =
                                std::dynamic_pointer_cast<Metiorite>(obj);
                            pMetiorite)
                    {
                        sf::Vector2f position = pMetiorite->getTarget();
                        gameScene.ReleaseSceneObject(obj);
                        gameScene.AddSceneObject(make_unique<Explosion>(position, 20.f));
                    }
                    else if(shared_ptr<Explosion> pExplotion =
                                std::dynamic_pointer_cast<Explosion>(obj);
                            pExplotion)
                    {
                        gameScene.ReleaseSceneObject(obj);
                    }
                }
            }
            break;
        case State::State::Pause:
            for(auto obj : menuScene.getVec())
            {
                if(!obj->update(delta))
                {
                    if(shared_ptr<PauseMenu> pmenu = std::dynamic_pointer_cast<PauseMenu>(obj);
                       pmenu)
                    {
                        pmenu->setActive(true);
                    }
                    // l�gg till mainmenu och scoreboard
                }
            }
            break;
        case State::State::Menu:
            for(auto obj : menuScene.getVec())
            {
                if(!obj->update(delta))
                {
                    if(shared_ptr<PauseMenu> pmenu = std::dynamic_pointer_cast<PauseMenu>(obj);
                       pmenu)
                    {
                        pmenu->setActive(false);
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
    window.clear();
    switch(gameState)
    {
        case State::State::InGame:
            window.draw(backgroundSprite);
            for(auto it = gameScene.begin(); it != gameScene.end(); it++)
            {
                window.draw(**it);
            }
            break;
        case State::State::Pause:
            for(auto it = menuScene.begin(); it != menuScene.end(); it++)
            {
                window.draw(**it);
            }
            break;
        case State::Menu: break;
        case State::Exit: break;
    }

    window.display();
    // fCounter.updateFps();
    // fCounter.printFps();
}

void Game::GameLoop()
{
    InitGame();

    while(gameState != State::Exit && window.isOpen())
    {
        HandleInput();
        UpdateGame();
        UpdateScreen();
        ComposeFrame();
    }
}
