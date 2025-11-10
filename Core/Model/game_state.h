#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "chess_board.h"
#include "../common/enums.h"
#include <mutex>

class GameState {
public:
    GameState();

    // 获取当前游戏状态
    GameStatus getStatus() const;

    // 设置游戏状态
    void setStatus(GameStatus status);

    // 获取当前玩家
    PieceColor getCurrentPlayer() const;

    // 切换当前玩家
    void switchPlayer();

    // 获取棋盘
    ChessBoard& getBoard();
    const ChessBoard& getBoard() const;

    // 重置游戏状态
    void reset();

    // 获取玩家角色
    PlayerRole getPlayerRole() const;

    // 设置玩家角色
    void setPlayerRole(PlayerRole role);

private:
    mutable std::mutex m_mutex;       // 互斥锁，保证线程安全
    GameStatus m_status;              // 游戏状态
    PieceColor m_currentPlayer;       // 当前回合玩家
    ChessBoard m_board;               // 棋盘
    PlayerRole m_playerRole;          // 本地玩家角色
};

#endif // GAME_STATE_H