// Ramanooj
#ifndef TIMING_H
#define TIMING_H

class Timing
{
public:
    Timing();
    ~Timing();

    void Tick();
    float GetDeltaTime() const;
    float GetTotalTime() const;
    float GetFPS() const;

private:
    float m_deltaTime;
    float m_totalTime;
    unsigned int m_lastTick;
    float m_fps;
    unsigned int m_frameCount;
    unsigned int m_lastFPSUpdate;
};

#endif // TIMING_H
