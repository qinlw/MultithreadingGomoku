#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "../model/chess_board.h"
#include "../common/enums.h"

class GameRules {
public:
    // 判断指定位置落子后是否获胜
    static bool isWin(const ChessBoard& board, int x, int y, PieceColor color);

    // 判断是否平局（棋盘已满）
    static bool isDraw(const ChessBoard& board);

    // 检查是否有禁手（简化版，仅检查基本禁手）
    static bool hasForbiddenMove(const ChessBoard& board, int x, int y, PieceColor color);
};

#endif // GAME_RULES_H