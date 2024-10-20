//Quinton
#ifndef RESOURCE_H
#define RESOURCE_H

#include "StandardIncludes.h"

class Resource
{
public:
    // Constructors/Destructors
    Resource();
    virtual ~Resource();

    // Serialization methods
    virtual void Serialize(std::ostream& _stream);
    virtual void Deserialize(std::istream& _stream);
    virtual void ToString() const;

    // Reference counting (if needed)
    void AddRef();
    void Release();

protected:
    // Members
    std::string m_resourceName;
    int m_refCount;
};

#endif // RESOURCE_H
