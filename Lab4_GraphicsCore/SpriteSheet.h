// Quinton
#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "StandardIncludes.h"

class SpriteSheet
{
public:
    SpriteSheet(SDL_Renderer* renderer);
    ~SpriteSheet();

    bool Load(const std::string& filePath);
    void SetGridSize(int columns, int rows, int frameWidth, int frameHeight);
    void GetFrameRect(int frameIndex, SDL_Rect& rect) const;
    int GetFrameCount() const;
    int GetFrameWidth() const;
    int GetFrameHeight() const;
    SDL_Texture* GetTexture() const;

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    int m_columns;
    int m_rows;
    int m_frameWidth;
    int m_frameHeight;
    int m_frameCount;
};

#endif // SPRITESHEET_H
