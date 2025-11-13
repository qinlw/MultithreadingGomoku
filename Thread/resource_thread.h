#ifndef RESOURCE_THREAD_H
#define RESOURCE_THREAD_H

#include "base_thread.h"
#include "../Resource/resource_def.h"
#include <memory>

// 资源加载线程：异步加载图片等资源，避免阻塞UI线程
class ResourceThread : public BaseThread {
public:
    ResourceThread();

    // 加载图片资源（通过消息队列发送加载请求）
    void loadImage(ImageId id);

protected:
    void run() override;
    void handleMessage(std::shared_ptr<Message> msg) override;

private:
    // 处理图片加载请求
    void handleLoadImage(ImageId id);
};

// 资源加载完成消息（供UI线程接收）
class ResourceLoadedMsg : public Message {
public:
    ResourceLoadedMsg(ImageId id, bool success)
        : Message(MsgType::ResourceLoaded), m_id(id), m_success(success) {
    }

    ImageId id() const { return m_id; }
    bool success() const { return m_success; }

private:
    ImageId m_id;
    bool m_success;
};

#endif // RESOURCE_THREAD_H