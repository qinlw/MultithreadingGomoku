#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include "message.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

class MsgQueue {
public:
    MsgQueue() = default;
    ~MsgQueue() = default;

    // 禁止拷贝
    MsgQueue(const MsgQueue&) = delete;
    MsgQueue& operator=(const MsgQueue&) = delete;

    // 加入消息
    void push(std::shared_ptr<Message> msg) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(msg);
        m_cond.notify_one();
    }

    // 取出消息（阻塞等待）
    std::shared_ptr<Message> pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]() { return !m_queue.empty(); });
        auto msg = m_queue.front();
        m_queue.pop();
        return msg;
    }

    // 尝试取出消息（非阻塞）
    bool tryPop(std::shared_ptr<Message>& msg) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty()) return false;
        msg = m_queue.front();
        m_queue.pop();
        return true;
    }

    // 清空队列
    void clear() {
        std::lock_guard<std::mutex> lock(m_mutex);
        while (!m_queue.empty()) {
            m_queue.pop();
        }
    }

private:
    std::queue<std::shared_ptr<Message>> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
};

#endif // MSG_QUEUE_H