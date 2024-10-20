// Ramanooj
#include "Timing.h"
#include <SDL.h>

Timing::Timing()
    : m_deltaTime(0.0f),
    m_totalTime(0.0f),
    m_lastTick(SDL_GetTicks()),
    m_fps(0.0f),
    m_frameCount(0),
    m_lastFPSUpdate(SDL_GetTicks())
{
}

Timing::~Timing()
{
}

void Timing::Tick()
{
    unsigned int currentTick = SDL_GetTicks();
    m_deltaTime = (currentTick - m_lastTick) / 1000.0f;
    m_lastTick = currentTick;
    m_totalTime += m_deltaTime;

    m_frameCount++;
    if (currentTick - m_lastFPSUpdate >= 1000)
    {
        m_fps = m_frameCount / ((currentTick - m_lastFPSUpdate) / 1000.0f);
        m_frameCount = 0;
        m_lastFPSUpdate = currentTick;
    }
}

float Timing::GetDeltaTime() const
{
    return m_deltaTime;
}

float Timing::GetTotalTime() const
{
    return m_totalTime;
}

float Timing::GetFPS() const
{
    return m_fps;
}
