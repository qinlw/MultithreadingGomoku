#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include <thread>
#include <atomic>
#include <memory>
#include "../msg/msg_queue.h"

class BaseThread {
public:
    BaseThread();
    virtual ~BaseThread();

    // 启动线程
    void start();

    // 停止线程
    void stop();

    // 判断线程是否运行
    bool isRunning() const { return m_running; }

    // 获取消息队列（用于向该线程发送消息）
    std::shared_ptr<MsgQueue> getMsgQueue() const { return m_msgQueue; }

protected:
    // 线程主循环
    virtual void run() = 0;

    // 处理消息（子类实现）
    virtual void handleMessage(std::shared_ptr<Message> msg) = 0;

    std::atomic<bool> m_running;          // 线程运行状态
    std::thread m_thread;                 // 线程对象
    std::shared_ptr<MsgQueue> m_msgQueue; // 消息队列
};

#endif // BASE_THREAD_H