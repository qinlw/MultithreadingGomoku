#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include "base_thread.h"
#include "../core/model/game_state.h"
#include "../core/logic/game_rules.h"
#include "../core/logic/move_validator.h"
#include <memory>

// 前置声明
class NetworkThread;

class GameThread : public BaseThread {
public:
    GameThread(std::shared_ptr<NetworkThread> networkThread);

    // 获取游戏状态
    std::shared_ptr<GameState> getGameState() const { return m_gameState; }

    // 设置UI线程的消息队列
    void setUiMsgQueue(std::shared_ptr<MsgQueue> queue) { m_uiMsgQueue = queue; }

protected:
    void run() override;
    void handleMessage(std::shared_ptr<Message> msg) override;

private:
    // 处理落子请求
    void handleMoveRequest(const MoveRequestMsg* moveMsg);

    // 处理游戏开始
    void handleGameStart();

    // 处理游戏重启
    void handleGameRestart();

    // 处理网络收到的落子
    void handleNetworkMove(const QPoint& pos, PieceColor color);

    // 发送消息到UI线程
    void sendToUi(std::shared_ptr<Message> msg);

    // 发送消息到网络线程
    void sendToNetwork(std::shared_ptr<Message> msg);

    std::shared_ptr<GameState> m_gameState;       // 游戏状态
    std::shared_ptr<NetworkThread> m_networkThread; // 网络线程
    std::shared_ptr<MsgQueue> m_uiMsgQueue;       // UI线程消息队列
};

#endif // GAME_THREAD_H