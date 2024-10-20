//Qunton
#ifndef SPRITEANIM_H
#define SPRITEANIM_H

#include "Resource.h"
#include "ObjectPool.h"

class SpriteAnim : public Resource
{
public:
    // Constructors/Destructors
    SpriteAnim();
    virtual ~SpriteAnim();

    // Accessors
    short GetClipCurrent() const;
    short GetClipEnd() const;

    // Methods
    void Create(short _clipStart, short _clipCount, float _clipSpeed);
    void Update(float _deltaTime);
    void Reset();

    // Serialization
    virtual void Serialize(std::ostream& _stream) override;
    virtual void Deserialize(std::istream& _stream) override;
    virtual void ToString() const override;

    // Object Pool
    static ObjectPool<SpriteAnim>* Pool;

private:
    // Members
    short m_clipStart;
    short m_clipCount;
    short m_clipEnd;
    float m_clipCurrent;
    float m_clipSpeed;

    void ClearMemory();
};

#endif // SPRITEANIM_H
