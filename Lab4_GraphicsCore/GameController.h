// Ramanooj
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Renderer.h"
#include "Timing.h"
#include "TTFont.h"
#include "Warrior.h"
#include "Stone.h"
#include <vector>

class GameController
{
public:
    GameController();
    ~GameController();

    void RunGame();

private:
    void LoadLevel1();
    void LoadLevel2();
    void Update(float deltaTime);
    void Render();
    void SaveGameState(const std::string& filename);
    void LoadGameState(const std::string& filename);

    int m_currentLevel;
    bool m_isRunning;
    float m_timeSinceLastSave;

    Renderer* m_renderer;
    Timing* m_timing;
    TTFont* m_font;

    SDL_Event m_sdlEvent;

    std::vector<Warrior*> m_warriors;
    std::vector<Stone*> m_stones;

    float m_stoneSpawnTimer;
    float m_stoneSpawnInterval;
    SpriteSheet* m_stoneSpriteSheet;
};

#endif // GAMECONTROLLER_H
