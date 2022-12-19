#include <SFML/Graphics.hpp>
#include <ctime>

class FrameCounter
{
    sf::Clock clock = sf::Clock::Clock();
    sf::Time lTime = clock.getElapsedTime();
    sf::Time cTime;
    float fps;

  public:
    void updateFps();
    float getFps() const;
    void printFps() const;
};
