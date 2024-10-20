// Ramanooj
#include "TTFont.h"

TTFont::TTFont()
    : m_font(nullptr)
{
}

TTFont::~TTFont()
{
    Shutdown();
}

bool TTFont::Initialize(const std::string& fontPath, int fontSize)
{
    m_font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!m_font)
    {
        std::cerr << "Failed to load font: " << fontPath << " Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void TTFont::Shutdown()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

void TTFont::Write(SDL_Renderer* renderer, const std::string& text, SDL_Color color, SDL_Point position)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, text.c_str(), color);
    if (textSurface)
    {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect renderQuad = { position.x, position.y, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
    else
    {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
    }
}
