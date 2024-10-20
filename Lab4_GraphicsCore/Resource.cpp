//Quniton
#include "Resource.h"

Resource::Resource()
    : m_refCount(1) // Initialize reference count to 1
{
}

Resource::~Resource()
{
    std::cout << "Resource " << this << " destroyed." << std::endl;
}

void Resource::AddRef()
{
    ++m_refCount;
    std::cout << "Resource " << this << " AddRef, refCount: " << m_refCount << std::endl;
}

void Resource::Release()
{
    --m_refCount;
    std::cout << "Resource " << this << " Release, refCount: " << m_refCount << std::endl;
    if (m_refCount == 0)
    {
        std::cout << "Deleting resource " << this << std::endl;
        delete this;
    }
}

void Resource::Serialize(std::ostream& _stream)
{
    // Serialize the resource name
    size_t nameLength = m_resourceName.size();
    _stream.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    _stream.write(m_resourceName.c_str(), nameLength);
}

void Resource::Deserialize(std::istream& _stream)
{
    // Deserialize the resource name
    size_t nameLength = 0;
    _stream.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

    m_resourceName.resize(nameLength);
    _stream.read(&m_resourceName[0], nameLength);
}

void Resource::ToString() const
{
    std::cout << "Resource Name: " << m_resourceName << std::endl;
}

