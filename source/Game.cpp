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
    sDrawables.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width / 6, height - 50))); // Tower left
    sDrawables.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width / 2, height - 50))); // Tower middle
    sDrawables.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width - (width / 6), height - 50))); // Tower right
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
            if(event.key.code == sf::Mouse::Left)
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
                    auto closestTowerPtr = sDrawables.GetClosestFirableTower(mousePosition);
                    if(closestTowerPtr != nullptr)
                    {
                        closestTowerPtr->fireMissile();
                        sDrawables.AddSceneObject(
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
    }
}

void Game::UpdateScreen()
{
    sf::Time delta = clock.restart();

    switch(gameState)
    {
        case State::State::InGame:
            for(auto obj : sDrawables.getVec())
            {
                if(!obj->update(delta))
                {
                    if(shared_ptr<Missile> pFirework = std::dynamic_pointer_cast<Missile>(obj);
                       pFirework)
                    {
                        sf::Vector2f position = pFirework->getTarget();
                        sDrawables.ReleaseSceneObject(obj);
                        sDrawables.AddSceneObject(make_unique<Explosion>(position, 20.f));
                    }
                    else if(shared_ptr<Metiorite> pMetiorite =
                                std::dynamic_pointer_cast<Metiorite>(obj);
                            pMetiorite)
                    {
                        sf::Vector2f position = pMetiorite->getTarget();
                        sDrawables.ReleaseSceneObject(obj);
                        sDrawables.AddSceneObject(make_unique<Explosion>(position, 20.f));
                    }
                    else if(shared_ptr<Explosion> pExplotion =
                                std::dynamic_pointer_cast<Explosion>(obj);
                            pExplotion)
                    {
                        sDrawables.ReleaseSceneObject(obj);
                    }
                }
            }
            break;
        case State::State::Pause:
    }
}

void Game::ComposeFrame()
{
    // Drawing
    window.clear();
    window.draw(backgroundSprite);
    for(auto it = sDrawables.begin(); it != sDrawables.end(); it++)
    {
        window.draw(**it);
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
