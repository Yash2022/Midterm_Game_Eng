//Yash
#ifndef ASSETCONTROLLER_H
#define ASSETCONTROLLER_H

#include "StandardIncludes.h"
#include "Singleton.h"
#include "Resource.h"
#include <unordered_map>
#include <string>

class AssetController : public Singleton<AssetController>
{
public:
    AssetController();
    virtual ~AssetController();

    void Initialize(size_t memorySize);
    void Shutdown();

    template <typename T>
    T* LoadAsset(const std::string& filePath);

    void AddAsset(const std::string& name, Resource* resource);

private:
    std::unordered_map<std::string, Resource*> m_assets;
};

#endif // ASSETCONTROLLER_H
