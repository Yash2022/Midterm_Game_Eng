//Yash and Quinton
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer)
    : m_renderer(renderer),
    m_texture(nullptr),
    m_columns(0),
    m_rows(0),
    m_frameWidth(0),
    m_frameHeight(0),
    m_frameCount(0)
{
}

SpriteSheet::~SpriteSheet()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

bool SpriteSheet::Load(const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image: " << filePath << " Error: " << IMG_GetError() << std::endl;
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    if (!m_texture)
    {
        std::cerr << "Failed to create texture from surface. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void SpriteSheet::SetGridSize(int columns, int rows, int frameWidth, int frameHeight)
{
    m_columns = columns;
    m_rows = rows;
    m_frameWidth = frameWidth;
    m_frameHeight = frameHeight;
    m_frameCount = columns * rows;
}

void SpriteSheet::GetFrameRect(int frameIndex, SDL_Rect& rect) const
{
    int x = (frameIndex % m_columns) * m_frameWidth;
    int y = (frameIndex / m_columns) * m_frameHeight;

    rect.x = x;
    rect.y = y;
    rect.w = m_frameWidth;
    rect.h = m_frameHeight;
}

int SpriteSheet::GetFrameCount() const
{
    return m_frameCount;
}

int SpriteSheet::GetFrameWidth() const
{
    return m_frameWidth;
}

int SpriteSheet::GetFrameHeight() const
{
    return m_frameHeight;
}

SDL_Texture* SpriteSheet::GetTexture() const
{
    return m_texture;
}
