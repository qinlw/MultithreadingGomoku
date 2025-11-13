#include "resource_manager.h"
#include "../Core/Common/utils.h"
#include <QImage>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadImage(ImageId id) {
    QString path;
    switch (id) {
    case ImageId::Board: path = ResourcePath::Board; break;
    case ImageId::BlackPiece: path = ResourcePath::BlackPiece; break;
    case ImageId::WhitePiece: path = ResourcePath::WhitePiece; break;
    case ImageId::ButtonStart: path = ResourcePath::ButtonStart; break;
    default:
        Utils::logError("Unknown image ID");
        return false;
    }

    QImage image(path);
    if (image.isNull()) {
        Utils::logError("Failed to load image: " + Utils::qstringToStdString(path));
        return false;
    }

    m_imageCache[id] = image;
    Utils::logInfo("Loaded image: " + Utils::qstringToStdString(path));
    return true;
}

QImage ResourceManager::getImage(ImageId id) const {
    auto it = m_imageCache.find(id);
    if (it != m_imageCache.end()) {
        return it->second;
    }
    Utils::logError("Image not loaded: " + std::to_string(static_cast<int>(id)));
    return QImage();
}

void ResourceManager::release(ImageId id) {
    auto it = m_imageCache.find(id);
    if (it != m_imageCache.end()) {
        m_imageCache.erase(it);
        Utils::logInfo("Released image: " + std::to_string(static_cast<int>(id)));
    }
}

void ResourceManager::releaseAll() {
    m_imageCache.clear();
    Utils::logInfo("Released all resources");
}