// Yash
#include "Stone.h"
#include "Renderer.h"
#include <iostream> 

Stone::Stone(SpriteSheet* spriteSheet, float speed, float animSpeed)
    : m_spriteSheet(spriteSheet),
    m_speed(speed),
    m_animSpeed(animSpeed),
    m_position(0.0f, 0.0f),
    m_scale(1.0f),
    m_animationTimer(0.0f),
    m_currentFrame(0)
{
    if (m_spriteSheet)
    {
        m_texture = m_spriteSheet->GetTexture();
    }
    else
    {
        m_texture = nullptr;
        std::cerr << "SpriteSheet is null in Stone constructor." << std::endl;
    }
}

Stone::~Stone()
{
    //
}

void Stone::Update(float deltaTime)
{
    m_position.Y += m_speed * deltaTime;

    m_animationTimer += deltaTime * m_animSpeed;
    if (m_animationTimer >= 1.0f)
    {
        m_animationTimer = 0.0f;
        if (m_spriteSheet)
        {
            m_currentFrame = (m_currentFrame + 1) % m_spriteSheet->GetFrameCount();
        }
    }
}

void Stone::Render(Renderer* renderer)
{
    if (!m_texture)
    {
        std::cerr << "Stone texture is null. Cannot render." << std::endl;
        return;
    }

    SDL_Rect srcRect;
    m_spriteSheet->GetFrameRect(m_currentFrame, srcRect);

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_position.X);
    destRect.y = static_cast<int>(m_position.Y);
    destRect.w = static_cast<int>(srcRect.w * m_scale);
    destRect.h = static_cast<int>(srcRect.h * m_scale);

    renderer->RenderTexture(m_texture, &srcRect, &destRect);
}

void Stone::SetPosition(float x, float y)
{
    m_position.X = x;
    m_position.Y = y;
}

void Stone::SetScale(float scale)
{
    m_scale = scale;
}

float Stone::GetWidth() const
{
    return m_spriteSheet->GetFrameWidth() * m_scale;
}

float Stone::GetHeight() const
{
    return m_spriteSheet->GetFrameHeight() * m_scale;
}

Point Stone::GetPosition() const
{
    return m_position;
}
