//Quinton
#include "SpriteAnim.h"
#include <iostream>

// Static Pool definition
ObjectPool<SpriteAnim>* SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

SpriteAnim::SpriteAnim()
{
    ClearMemory();
}

SpriteAnim::~SpriteAnim()
{
    // Cleanup if necessary
}

void SpriteAnim::ClearMemory()
{
    m_clipStart = 0;
    m_clipCount = 0;
    m_clipEnd = 0;
    m_clipCurrent = 0.0f;
    m_clipSpeed = 0.0f;
}

void SpriteAnim::Create(short _clipStart, short _clipCount, float _clipSpeed)
{
    m_clipStart = _clipStart;
    m_clipCount = _clipCount;
    m_clipSpeed = _clipSpeed;
    m_clipCurrent = static_cast<float>(m_clipStart);
    m_clipEnd = m_clipStart + m_clipCount - 1;
}

void SpriteAnim::Update(float _deltaTime)
{
    m_clipCurrent += m_clipSpeed * _deltaTime;
    if (m_clipCurrent > m_clipEnd)
    {
        m_clipCurrent = static_cast<float>(m_clipStart);
    }
}

void SpriteAnim::Reset()
{
    m_clipCurrent = static_cast<float>(m_clipStart);
}

short SpriteAnim::GetClipCurrent() const
{
    return static_cast<short>(m_clipCurrent);
}

short SpriteAnim::GetClipEnd() const
{
    return m_clipEnd;
}

void SpriteAnim::Serialize(std::ostream& _stream)
{
    _stream.write(reinterpret_cast<const char*>(&m_clipStart), sizeof(m_clipStart));
    _stream.write(reinterpret_cast<const char*>(&m_clipCount), sizeof(m_clipCount));
    _stream.write(reinterpret_cast<const char*>(&m_clipSpeed), sizeof(m_clipSpeed));
    _stream.write(reinterpret_cast<const char*>(&m_clipCurrent), sizeof(m_clipCurrent));
    Resource::Serialize(_stream);
}

void SpriteAnim::Deserialize(std::istream& _stream)
{
    _stream.read(reinterpret_cast<char*>(&m_clipStart), sizeof(m_clipStart));
    _stream.read(reinterpret_cast<char*>(&m_clipCount), sizeof(m_clipCount));
    _stream.read(reinterpret_cast<char*>(&m_clipSpeed), sizeof(m_clipSpeed));
    _stream.read(reinterpret_cast<char*>(&m_clipCurrent), sizeof(m_clipCurrent));
    m_clipEnd = m_clipStart + m_clipCount - 1;
    Resource::Deserialize(_stream);
}

void SpriteAnim::ToString() const
{
    std::cout << "SpriteAnim: "
        << "Start: " << m_clipStart
        << ", Count: " << m_clipCount
        << ", Speed: " << m_clipSpeed
        << ", Current: " << m_clipCurrent
        << std::endl;
}
