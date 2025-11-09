#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include "../model/chess_board.h"
#include "../common/enums.h"
#include <QPoint>

class MoveValidator {
public:
    // 验证落子是否合法
    static bool isValidMove(const ChessBoard& board, const QPoint& pos, PieceColor color);

    // 转换屏幕坐标到棋盘坐标
    static QPoint screenToBoard(const QPoint& screenPos);

    // 转换棋盘坐标到屏幕坐标
    static QPoint boardToScreen(const QPoint& boardPos);
};

#endif // MOVE_VALIDATOR_H