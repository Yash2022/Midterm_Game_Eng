//Yash
#include "AssetController.h"
#include "Texture.h"
#include <iostream>

AssetController::AssetController()
{
}

AssetController::~AssetController()
{
    Shutdown();
}

void AssetController::Initialize(size_t memorySize)
{
    // Initialize asset controller if needed
}

void AssetController::Shutdown()
{
    std::cout << "Asset count before shutdown: " << m_assets.size() << std::endl;

    for (auto& assetPair : m_assets)
    {
        if (assetPair.second)
        {
            assetPair.second->Release(); // Use reference counting
        }
        else
        {
            std::cout << "Warning: Null resource for key: " << assetPair.first << std::endl;
        }
    }
    m_assets.clear();
}

template <typename T>
T* AssetController::LoadAsset(const std::string& filePath)
{
    // Check if asset is already loaded
    if (m_assets.find(filePath) != m_assets.end())
    {
        T* asset = dynamic_cast<T*>(m_assets[filePath]);
        if (asset)
        {
            asset->AddRef();
            return asset;
        }
    }

    // Load new asset
    T* asset = new T();
    if (!asset->Load(filePath))
    {
        delete asset;
        return nullptr;
    }

    asset->AddRef(); // Increase reference count
    m_assets[filePath] = asset;
    return asset;
}

// Explicit template instantiation for Texture (if needed)
template Texture* AssetController::LoadAsset<Texture>(const std::string& filePath);
