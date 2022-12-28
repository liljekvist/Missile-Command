#include <SFML/Graphics.hpp>
#include <ctime>

class FrameCounter
{
    sf::Clock m_clock;
    sf::Time m_lTime = m_clock.getElapsedTime();
    sf::Time m_cTime;
    float m_fps = 0.0F;

  public:
    void updateFps();
    [[nodiscard]] auto getFps() const -> float;
    void printFps() const;
};
