#ifndef NETWORK_THREAD_H
#define NETWORK_THREAD_H

#include "base_thread.h"
#include <string>

// 前置声明
class GameThread;

class NetworkThread : public BaseThread {
public:
    NetworkThread();

    // 设置游戏线程
    void setGameThread(std::shared_ptr<GameThread> gameThread) { m_gameThread = gameThread; }

    // 连接到服务器
    void connectToServer(const std::string& ip, int port);

    // 断开连接
    void disconnect();

protected:
    void run() override;
    void handleMessage(std::shared_ptr<Message> msg) override;

private:
    // 发送消息到游戏线程
    void sendToGame(std::shared_ptr<Message> msg);

    // 处理接收到的网络数据
    void handleNetworkData(const char* data, int len);

    std::shared_ptr<GameThread> m_gameThread; // 游戏线程
    bool m_connected;                         // 连接状态
    std::string m_serverIp;                   // 服务器IP
    int m_serverPort;                         // 服务器端口
};

#endif // NETWORK_THREAD_H