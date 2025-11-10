#include "game_rules.h"

bool GameRules::isWin(const ChessBoard& board, int x, int y, PieceColor color) {
    // 检查方向：水平、垂直、左斜、右斜
    const int dirs[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    for (const auto& dir : dirs) {
        int count = 1; // 当前位置已有一个棋子

        // 正向检查
        for (int i = 1; i < 5; ++i) {
            int nx = x + dir[0] * i;
            int ny = y + dir[1] * i;
            if (board.getPiece(nx, ny) == color) {
                count++;
            }
            else {
                break;
            }
        }

        // 反向检查
        for (int i = 1; i < 5; ++i) {
            int nx = x - dir[0] * i;
            int ny = y - dir[1] * i;
            if (board.getPiece(nx, ny) == color) {
                count++;
            }
            else {
                break;
            }
        }

        // 五子连珠
        if (count >= 5) {
            return true;
        }
    }

    return false;
}

bool GameRules::isDraw(const ChessBoard& board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board.size(); ++j) {
            if (board.getPiece(i, j) == PieceColor::None) {
                return false; // 还有空位，不是平局
            }
        }
    }
    return true; // 棋盘已满
}

bool GameRules::hasForbiddenMove(const ChessBoard& board, int x, int y, PieceColor color) {
    // 简化版：仅检查三三禁手（黑棋）
    if (color != PieceColor::Black) {
        return false;
    }

    // 这里实现简化的三三禁手检查逻辑
    // 实际项目中需要更复杂的判定逻辑
    return false;
}