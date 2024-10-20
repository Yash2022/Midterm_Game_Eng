// Quinton
#include "Renderer.h"

Renderer::Renderer()
    : m_window(nullptr),
    m_renderer(nullptr),
    m_screenWidth(0),
    m_screenHeight(0)
{
}

Renderer::~Renderer()
{
    Shutdown();
}

Renderer& Renderer::Instance()
{
    static Renderer instance;
    return instance;
}


bool Renderer::Initialize(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
    if (!m_window)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::Shutdown()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Renderer::ClearScreen()
{
    SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Renderer::RenderTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* destRect)
{
    SDL_RenderCopy(m_renderer, texture, srcRect, destRect);
}

SDL_Renderer* Renderer::GetSDLRenderer() const
{
    return m_renderer;
}

int Renderer::GetScreenWidth() const
{
    return m_screenWidth;
}

int Renderer::GetScreenHeight() const
{
    return m_screenHeight;
}
