// Yash
#ifndef STONE_H
#define STONE_H

#include "SpriteSheet.h"
#include "BasicStructs.h"

class Renderer;

class Stone
{
public:
    Stone(SpriteSheet* spriteSheet, float speed, float animSpeed);
    ~Stone();

    void Update(float deltaTime);
    void Render(Renderer* renderer);
    void SetPosition(float x, float y);
    void SetScale(float scale);
    float GetWidth() const;
    float GetHeight() const;
    Point GetPosition() const;

private:
    SpriteSheet* m_spriteSheet;
    SDL_Texture* m_texture;
    Point m_position;
    float m_speed;
    float m_animSpeed;
    float m_scale;
    float m_animationTimer;
    int m_currentFrame;
};

#endif // STONE_H
