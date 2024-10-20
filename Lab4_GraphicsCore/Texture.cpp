//yash
#include "Texture.h"
#include "Renderer.h"

Texture::Texture()
    : m_texture(nullptr), m_width(0), m_height(0)
{
}

Texture::~Texture()
{
    Free();
}

bool Texture::Load(const std::string& _filePath)
{
    Free();

    m_resourceName = _filePath;

    SDL_Surface* loadedSurface = IMG_Load(_filePath.c_str());
    if (loadedSurface == nullptr)
    {
        std::cerr << "Unable to load image " << _filePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(Renderer::Instance().GetSDLRenderer(), loadedSurface);
    if (m_texture == nullptr)
    {
        std::cerr << "Unable to create texture from " << _filePath << "! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    m_width = loadedSurface->w;
    m_height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    return true;
}

void Texture::Free()
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
        m_resourceName = "";
    }
}

int Texture::GetWidth() const
{
    return m_width;
}

int Texture::GetHeight() const
{
    return m_height;
}

SDL_Texture* Texture::GetSDLTexture() const
{
    return m_texture;
}

void Texture::Serialize(std::ostream& _stream)
{
    Resource::Serialize(_stream);

    _stream.write(reinterpret_cast<const char*>(&m_width), sizeof(m_width));
    _stream.write(reinterpret_cast<const char*>(&m_height), sizeof(m_height));

}

void Texture::Deserialize(std::istream& _stream)
{
    Resource::Deserialize(_stream);

    _stream.read(reinterpret_cast<char*>(&m_width), sizeof(m_width));
    _stream.read(reinterpret_cast<char*>(&m_height), sizeof(m_height));

    Load(m_resourceName);
}

void Texture::ToString() const
{
    std::cout << "Texture: " << m_resourceName
        << ", Width: " << m_width
        << ", Height: " << m_height << std::endl;
}
