#pragma once
#include <SFML/Graphics.hpp>

// This exists to avoid loading the Assets multiple times :D

class Assets
{
  public:
    static sf::Texture tower;
    static sf::Texture missile;
    static sf::Texture background;
    static sf::Texture explotionSheet;
    static sf::Texture metioriteSheet;
    static sf::Font textFont;
    static void loadAssets()
    {
#ifdef __linux__
        tower.loadFromFile("../assets/Tower.png");
        missile.loadFromFile("../assets/Missile.png");
        background.loadFromFile("../assets/background.jpg");
        explotionSheet.loadFromFile("../assets/explotionsheet.png");
        metioriteSheet.loadFromFile("../assets/metioritesheet.png");
        textFont.loadFromFile("../assets/NFagave.ttf");
#elif _WIN32
        tower.loadFromFile("assets/Tower.png");
        missile.loadFromFile("assets/Missile.png");
        background.loadFromFile("assets/background.jpg");
        explotionSheet.loadFromFile("assets/explotionsheet.png");
        metioriteSheet.loadFromFile("assets/metioritesheet.png");
        textFont.loadFromFile("assets/NFagave.ttf");
#else
        tower.loadFromFile("assets/Tower.png");
        missile.loadFromFile("assets/Missile.png");
        background.loadFromFile("assets/background.jpg");
        explotionSheet.loadFromFile("assets/explotionsheet.png");
        metioriteSheet.loadFromFile("assets/metioritesheet.png");
        textFont.loadFromFile("assets/NFagave.ttf");
#endif
    }
};
