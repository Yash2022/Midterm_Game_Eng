// Ramanooj
#ifndef TTFONT_H
#define TTFONT_H

#include "StandardIncludes.h"

class TTFont
{
public:
    TTFont();
    ~TTFont();

    bool Initialize(const std::string& fontPath, int fontSize);
    void Shutdown();

    void Write(SDL_Renderer* renderer, const std::string& text, SDL_Color color, SDL_Point position);

private:
    TTF_Font* m_font;
};

#endif // TTFONT_H
