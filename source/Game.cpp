#include "Game.hpp"

Game::Game(): width(800), height(600), window(sf::VideoMode(width, height, 32), "Missile Command")
{
    // wow such empty
}

Game::Game(int _width, int _height)
    : width(_width)
    , height(_height)
    , window(sf::VideoMode(width, height, 32), "Missile Command")
{
    // wow such empty
}

Game::~Game() {}

void Game::InitGame()
{
    // window.setFramerateLimit(60);
    // Init Test
    sDrawables.AddSceneObject(make_shared<Tower>(sf::Vector2f(250, height - 100)));
    sDrawables.AddSceneObject(make_shared<Tower>(sf::Vector2f(width / 2, height - 100)));
    sDrawables.AddSceneObject(make_shared<Tower>(sf::Vector2f(width - 250, height - 100)));
    sDrawables.AddSceneObject(make_shared<Missile>(sf::Vector2f(400, 600), sf::Vector2f(400, 200)));
    sDrawables.AddSceneObject(make_shared<Missile>(sf::Vector2f(450, 600), sf::Vector2f(400, 200)));
    sDrawables.AddSceneObject(make_shared<Missile>(sf::Vector2f(500, 600), sf::Vector2f(400, 200)));
    sDrawables.AddSceneObject(make_shared<Missile>(sf::Vector2f(500, 600), sf::Vector2f(400, 200)));
    sDrawables.AddSceneObject(make_shared<Missile>(sf::Vector2f(500, 600), sf::Vector2f(400, 200)));
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
            if(event.key.code == sf::Keyboard::Space)
                running = false;
        }
    }
}

void Game::UpdateGame()
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

            else // It's an explosion
            {
                int windowWidth = window.getSize().x;
                int windowHeight = window.getSize().y;
                sf::Vector2f begin(rand() % windowWidth, rand() % windowHeight);
                sf::Vector2f end(rand() % windowWidth, rand() % windowHeight);
                sDrawables.ReleaseSceneObject(obj);
                sDrawables.AddSceneObject(make_unique<Missile>(begin, end));
            }
        }
    }
}

void Game::DrawGame()
{
    // Drawing
    window.clear();
    for(auto it = sDrawables.begin(); it != sDrawables.end(); it++)
    {
        window.draw(**it);
    }
    window.display();
    fCounter.updateFps();
    fCounter.printFps();
}

void Game::GameLoop()
{
    InitGame();

    while(running && window.isOpen())
    {
        HandleInput();
        UpdateGame();
        DrawGame();
    }
}
