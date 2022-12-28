#include "FrameCounter.hpp"
#include <cmath>
#include <iostream>

void FrameCounter::updateFps()
{
    m_cTime = m_clock.getElapsedTime();
    m_fps = 1.0F / (m_cTime.asSeconds() - m_lTime.asSeconds());
    m_lTime = m_cTime;
}

auto FrameCounter::getFps() const -> float
{
    return m_fps;
}

void FrameCounter::printFps() const
{
    std::cout << "FPS: " << std::floor(m_fps) << std::endl;
}
