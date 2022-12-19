#include "Game.hpp"
#include <iostream>

Game::Game(): width(800), height(600), window(sf::VideoMode(width, height, 32), "Missile Command")
{
    Textures::loadAssets();
    backgroundSprite = sf::Sprite(Textures::background);

    backgroundSprite.setScale(
        width / backgroundSprite.getLocalBounds().width,
        height / backgroundSprite.getLocalBounds().height);
}

Game::Game(int _width, int _height)
    : width(_width)
    , height(_height)
    , window(sf::VideoMode(width, height, 32), "Missile Command")
{
    Textures::loadAssets(); // Need to load the background before making the sprite
    backgroundSprite = sf::Sprite(Textures::background);

    backgroundSprite.setScale(
        width / backgroundSprite.getLocalBounds().width,
        height / backgroundSprite.getLocalBounds().height);
}

Game::~Game() {}

void Game::InitGame()
{
    sDrawables.AddSceneObject(make_shared<Tower>(sf::Vector2f(250, height - 50))); // Tower left
    sDrawables.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width / 2, height - 50))); // Tower middle
    sDrawables.AddSceneObject(
        make_shared<Tower>(sf::Vector2f(width - 250, height - 50))); // Tower right
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
                running = false;
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.key.code == sf::Mouse::Left)
                inputBuffer.insert(std::pair(Action::Shoot, sf::Mouse::getPosition(window)));
        }
    }
}

void Game::UpdateGame()
{
    for(auto itr = inputBuffer.begin(); itr != inputBuffer.end();)
    {
        if(itr->first == Action::Shoot) // Action is shoot and any is mousePos
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
}

void Game::UpdateScreen()
{
    sf::Time delta = clock.restart();

    for(auto obj : sDrawables.getVec())
    {
        if(!obj->update(delta))
        {
            if(shared_ptr<Missile> pFirework = std::dynamic_pointer_cast<Missile>(obj); pFirework)
            {
                sf::Vector2f position = pFirework->getTarget();
                sDrawables.ReleaseSceneObject(obj);
                sDrawables.AddSceneObject(make_unique<Explosion>(position, 20.f));
            }
            else if(shared_ptr<Explosion> pExplotion = std::dynamic_pointer_cast<Explosion>(obj);
                    pExplotion)
            {
                int windowWidth = window.getSize().x;
                int windowHeight = window.getSize().y;
                sf::Vector2f begin(rand() % windowWidth, rand() % windowHeight);
                sf::Vector2f end(rand() % windowWidth, rand() % windowHeight);
                sDrawables.ReleaseSceneObject(obj);
            }
        }
    }
}

void Game::DrawGame()
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

    while(running && window.isOpen())
    {
        HandleInput();
        UpdateGame();
        UpdateScreen();
        DrawGame();
    }
}
