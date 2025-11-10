#include "game_thread.h"
#include "network_thread.h"
#include "../msg/message.h"
#include "../core/common/enums.h"

GameThread::GameThread(std::shared_ptr<NetworkThread> networkThread)
    : m_networkThread(networkThread),
    m_gameState(std::make_shared<GameState>()) {
}

void GameThread::run() {
    while (m_running) {
        auto msg = m_msgQueue->pop();
        handleMessage(msg);
    }
}

void GameThread::handleMessage(std::shared_ptr<Message> msg) {
    switch (msg->type()) {
    case MsgType::UIMoveRequest:
        handleMoveRequest(static_cast<MoveRequestMsg*>(msg.get()));
        break;
    case MsgType::UIGameStart:
        handleGameStart();
        break;
    case MsgType::UIGameRestart:
        handleGameRestart();
        break;
    case MsgType::NetworkMoveReceived:
        // 这里需要具体的消息解析，暂时简化
        break;
    default:
        break;
    }
}

void GameThread::handleMoveRequest(const MoveRequestMsg* moveMsg) {
    auto& board = m_gameState->getBoard();
    auto pos = moveMsg->pos();
    auto color = moveMsg->color();

    // 验证落子合法性
    if (!MoveValidator::isValidMove(board, pos, color)) {
        // 发送落子无效消息到UI
        return;
    }

    // 放置棋子
    if (board.placePiece(pos, color)) {
        // 检查是否获胜
        if (GameRules::isWin(board, pos.x(), pos.y(), color)) {
            GameStatus status = (color == PieceColor::Black) ?
                GameStatus::BlackWin : GameStatus::WhiteWin;
            m_gameState->setStatus(status);

            // 发送游戏结束消息到UI
            sendToUi(std::make_shared<GameStateMsg>(status, pos));
            // 发送游戏结束消息到网络
            sendToNetwork(std::make_shared<GameStateMsg>(status, pos));
        }
        // 检查是否平局
        else if (GameRules::isDraw(board)) {
            m_gameState->setStatus(GameStatus::Draw);
            sendToUi(std::make_shared<GameStateMsg>(GameStatus::Draw, pos));
            sendToNetwork(std::make_shared<GameStateMsg>(GameStatus::Draw, pos));
        }
        // 游戏继续
        else {
            m_gameState->switchPlayer();
            sendToUi(std::make_shared<GameStateMsg>(m_gameState->getStatus(), pos));
            sendToNetwork(std::make_shared<MoveRequestMsg>(pos, color));
        }
    }
}

void GameThread::handleGameStart() {
    m_gameState->reset();
    m_gameState->setStatus(GameStatus::Playing);
    sendToUi(std::make_shared<GameStateMsg>(GameStatus::Playing));
}

void GameThread::handleGameRestart() {
    handleGameStart(); // 重启逻辑与开始类似
}

void GameThread::handleNetworkMove(const QPoint& pos, PieceColor color) {
    auto& board = m_gameState->getBoard();

    if (board.placePiece(pos, color)) {
        // 检查是否获胜
        if (GameRules::isWin(board, pos.x(), pos.y(), color)) {
            GameStatus status = (color == PieceColor::Black) ?
                GameStatus::BlackWin : GameStatus::WhiteWin;
            m_gameState->setStatus(status);
            sendToUi(std::make_shared<GameStateMsg>(status, pos));
        }
        // 检查是否平局
        else if (GameRules::isDraw(board)) {
            m_gameState->setStatus(GameStatus::Draw);
            sendToUi(std::make_shared<GameStateMsg>(GameStatus::Draw, pos));
        }
        // 游戏继续
        else {
            m_gameState->switchPlayer();
            sendToUi(std::make_shared<GameStateMsg>(m_gameState->getStatus(), pos));
        }
    }
}

void GameThread::sendToUi(std::shared_ptr<Message> msg) {
    if (m_uiMsgQueue) {
        m_uiMsgQueue->push(msg);
    }
}

void GameThread::sendToNetwork(std::shared_ptr<Message> msg) {
    if (m_networkThread) {
        auto netQueue = m_networkThread->getMsgQueue();
        if (netQueue) {
            netQueue->push(msg);
        }
    }
}