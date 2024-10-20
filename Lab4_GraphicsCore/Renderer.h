// Quninton
#ifndef RENDERER_H
#define RENDERER_H

#include "StandardIncludes.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();

    static Renderer& Instance();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;


    void ClearScreen();
    void Present();

    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void RenderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* destRect);

    SDL_Renderer* GetSDLRenderer() const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_screenWidth;
    int m_screenHeight;
};

#endif // RENDERER_H
