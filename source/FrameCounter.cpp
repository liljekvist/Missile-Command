#include "FrameCounter.hpp"
#include <iostream>

void FrameCounter::updateFps()
{
    cTime = clock.getElapsedTime();
    fps = 1.0f / (cTime.asSeconds() - lTime.asSeconds());
    lTime = cTime;
}

float FrameCounter::getFps() const
{
    return fps;
}

void FrameCounter::printFps() const
{
    std::cout << "FPS: " << floor(fps) << std::endl;
}
