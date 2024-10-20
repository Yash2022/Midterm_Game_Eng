// Yash
#include "Warrior.h"
#include "Renderer.h"
#include "Stone.h"

Warrior::Warrior(SpriteSheet* spriteSheet, float speed, float animSpeed)
    : m_spriteSheet(spriteSheet),
    m_speed(speed),
    m_animSpeed(animSpeed),
    m_position(0.0f, 0.0f),
    m_scale(1.0f),
    m_isDead(false),
    m_animationTimer(0.0f),
    m_currentFrame(18)
{
    m_texture = m_spriteSheet->GetTexture();
}

Warrior::~Warrior()
{
}

void Warrior::Update(float deltaTime)
{
    if (!m_isDead)
    {
        m_position.X += m_speed * deltaTime;
    }

    m_animationTimer += deltaTime * m_animSpeed;
    if (m_animationTimer >= 1.0f)
    {
        m_animationTimer = 0.0f;

        m_currentFrame++;
        if (m_currentFrame > 22)
        {
            m_currentFrame = 19;
        }

    }
}


void Warrior::Render(Renderer* renderer)
{
    SDL_Rect srcRect;
    m_spriteSheet->GetFrameRect(m_currentFrame, srcRect);

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_position.X);
    destRect.y = static_cast<int>(m_position.Y);
    destRect.w = static_cast<int>(srcRect.w * m_scale);
    destRect.h = static_cast<int>(srcRect.h * m_scale);

    renderer->RenderTexture(m_texture, &srcRect, &destRect);
}

void Warrior::SetPosition(float x, float y)
{
    m_position.X = x;
    m_position.Y = y;
}

void Warrior::SetScale(float scale)
{
    m_scale = scale;
}

float Warrior::GetWidth() const
{
    return m_spriteSheet->GetFrameWidth() * m_scale;
}

float Warrior::GetHeight() const
{
    return m_spriteSheet->GetFrameHeight() * m_scale;
}

Point Warrior::GetPosition() const
{
    return m_position;
}

bool Warrior::IsDead() const
{
    return m_isDead;
}

void Warrior::Die()
{
    m_isDead = true;
    m_currentFrame = 0;
    m_animationTimer = 0.0f;
}

bool Warrior::AnimationFinished() const
{
    return m_isDead && m_currentFrame == m_spriteSheet->GetFrameCount() - 1;
}

bool Warrior::CollidesWith(const Stone* stone) const
{
    SDL_Rect warriorRect = { static_cast<int>(m_position.X), static_cast<int>(m_position.Y),
                             static_cast<int>(GetWidth()), static_cast<int>(GetHeight()) };

    SDL_Rect stoneRect = { static_cast<int>(stone->GetPosition().X), static_cast<int>(stone->GetPosition().Y),
                           static_cast<int>(stone->GetWidth()), static_cast<int>(stone->GetHeight()) };

    return SDL_HasIntersection(&warriorRect, &stoneRect);
}
