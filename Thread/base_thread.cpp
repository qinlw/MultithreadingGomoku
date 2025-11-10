#include "base_thread.h"

BaseThread::BaseThread() : m_running(false), m_msgQueue(std::make_shared<MsgQueue>()) {}

BaseThread::~BaseThread() {
    stop();
}

void BaseThread::start() {
    if (!m_running) {
        m_running = true;
        m_thread = std::thread(&BaseThread::run, this);
    }
}

void BaseThread::stop() {
    if (m_running) {
        m_running = false;
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }
}