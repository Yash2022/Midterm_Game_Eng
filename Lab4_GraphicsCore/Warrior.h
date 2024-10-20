// Yash
#ifndef WARRIOR_H
#define WARRIOR_H

#include "SpriteSheet.h"
#include "BasicStructs.h"

class Renderer;

class Warrior
{
public:
    Warrior(SpriteSheet* spriteSheet, float speed, float animSpeed);
    ~Warrior();

    void Update(float deltaTime);
    void Render(Renderer* renderer);
    void SetPosition(float x, float y);
    void SetScale(float scale);
    float GetWidth() const;
    float GetHeight() const;
    Point GetPosition() const;
    bool IsDead() const;
    void Die();
    bool AnimationFinished() const;
    bool CollidesWith(const class Stone* stone) const;

private:
    SpriteSheet* m_spriteSheet;
    SDL_Texture* m_texture;
    Point m_position;
    float m_speed;
    float m_animSpeed;
    float m_scale;
    bool m_isDead;
    float m_animationTimer;
    int m_currentFrame;
};

#endif // WARRIOR_H
