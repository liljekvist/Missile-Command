#pragma once
#include <SFML/Graphics.hpp>

// This exists to avoid loading the textures multiple times :D

class Textures
{
  public:
    static sf::Texture tower;
    static sf::Texture missile;
    static sf::Texture background;
    static sf::Texture explotionSheet;
    static void loadAssets()
    {
        bool towerLoaded = tower.loadFromFile("assets/Tower.png");
        bool missileLoaded = missile.loadFromFile("assets/Missile.png");
        bool backgroundLoaded = background.loadFromFile("assets/background.jpg");
        bool explotionSheetLoaded = explotionSheet.loadFromFile("assets/explotionsheet.png");
    }
};
