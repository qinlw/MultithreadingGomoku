#include "resource_thread.h"
#include "../Resource/resource_manager.h"
#include "../Core/Common/utils.h"

ResourceThread::ResourceThread() : BaseThread() {}

void ResourceThread::loadImage(ImageId id) {
    // 发送加载请求到自身消息队列
    auto msg = std::make_shared<Message>(MsgType::ResourceLoadRequest);
    // 这里简化处理，实际需封装带ImageId的消息
    m_msgQueue->push(msg);
}

void ResourceThread::run() {
    Utils::logInfo("Resource thread started");
    while (m_running) {
        auto msg = m_msgQueue->pop();
        handleMessage(msg);
    }
    Utils::logInfo("Resource thread stopped");
}

void ResourceThread::handleMessage(std::shared_ptr<Message> msg) {
    switch (msg->type()) {
    case MsgType::ResourceLoadRequest:
        // 实际应解析消息中的ImageId
        handleLoadImage(ImageId::Board); // 示例：加载棋盘图片
        break;
    default:
        Utils::logError("Unknown message type in resource thread");
        break;
    }
}

void ResourceThread::handleLoadImage(ImageId id) {
    bool success = ResourceManager::getInstance().loadImage(id);
    // 发送加载完成消息（可被UI线程接收）
    auto resultMsg = std::make_shared<ResourceLoadedMsg>(id, success);
    // 假设UI线程的消息队列通过外部设置，此处简化
}