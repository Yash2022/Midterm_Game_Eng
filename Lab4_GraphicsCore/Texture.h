//Yash
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"
#include "StandardIncludes.h"

class Texture : public Resource
{
public:
    // Constructors/Destructors
    Texture();
    virtual ~Texture();

    // Methods
    bool Load(const std::string& _filePath);
    void Free();

    // Accessors
    int GetWidth() const;
    int GetHeight() const;
    SDL_Texture* GetSDLTexture() const;

    // Serialization
    virtual void Serialize(std::ostream& _stream) override;
    virtual void Deserialize(std::istream& _stream) override;
    virtual void ToString() const override;

private:
    // Members
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
};

#endif // TEXTURE_H
