#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <QImage>
#include <unordered_map>
#include <memory>
#include "resource_def.h"

// 单例资源管理器：统一加载、缓存、释放资源
class ResourceManager {
public:
    // 获取单例实例
    static ResourceManager& getInstance();

    // 加载图片资源（缓存到内存）
    bool loadImage(ImageId id);

    // 获取图片资源（返回缓存的图片，若未加载则返回空）
    QImage getImage(ImageId id) const;

    // 释放指定资源
    void release(ImageId id);

    // 释放所有资源
    void releaseAll();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<ImageId, QImage> m_imageCache; // 图片缓存
};

#endif // RESOURCE_MANAGER_H