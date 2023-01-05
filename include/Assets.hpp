#pragma once
#include <SFML/Graphics.hpp>

// This exists to avoid loading the Assets multiple times :D

class Assets
{
  public:
    static sf::Texture tower;
    static sf::Texture missile;
    static sf::Texture background;
    static sf::Texture explotion_sheet;
    static sf::Texture metiorite_sheet;
    static sf::Font text_font;
    static void loadAssets()
    {
#ifdef __linux__
        tower.loadFromFile("../assets/Tower.png"); // Since its compiled from build folder instead
                                                   // of root we need to jump one more step out
        missile.loadFromFile("../assets/Missile.png");
        background.loadFromFile("../assets/background.jpg");
        explotion_sheet.loadFromFile("../assets/explotionsheet.png");
        metiorite_sheet.loadFromFile("../assets/metioritesheet.png");
        text_font.loadFromFile("../assets/NFagave.ttf");
#elif _WIN32
        tower.loadFromFile("assets/Tower.png");
        missile.loadFromFile("assets/Missile.png");
        background.loadFromFile("assets/background.jpg");
        explotion_sheet.loadFromFile("assets/explotionsheet.png");
        metiorite_sheet.loadFromFile("assets/metioritesheet.png");
        text_font.loadFromFile("assets/NFagave.ttf");
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
