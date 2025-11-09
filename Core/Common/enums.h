#ifndef ENUMS_H
#define ENUMS_H

// 棋子颜色
enum class PieceColor {
    None,   // 空
    Black,  // 黑棋
    White   // 白棋
};

// 游戏状态
enum class GameStatus {
    NotStarted,  // 未开始
    Playing,     // 进行中
    Paused,      // 暂停
    BlackWin,    // 黑棋胜利
    WhiteWin,    // 白棋胜利
    Draw         // 平局
};

// 玩家角色
enum class PlayerRole {
    None,     // 未分配
    Black,    // 黑棋玩家
    White,    // 白棋玩家
    Spectator // 观战者
};

#endif // ENUMS_H