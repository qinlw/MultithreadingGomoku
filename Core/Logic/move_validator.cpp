#include "move_validator.h"
#include "../common/define.h"
#include "game_rules.h"

bool MoveValidator::isValidMove(const ChessBoard& board, const QPoint& pos, PieceColor color) {
    // 检查位置是否有效
    if (!board.isValidPosition(pos)) {
        return false;
    }

    // 检查位置是否已有棋子
    if (board.getPiece(pos) != PieceColor::None) {
        return false;
    }

    // 检查是否有禁手
    if (GameRules::hasForbiddenMove(board, pos.x(), pos.y(), color)) {
        return false;
    }

    return true;
}

QPoint MoveValidator::screenToBoard(const QPoint& screenPos) {
    // 计算棋盘坐标（考虑偏移量和单元格大小）
    int x = (screenPos.x() - BOARD_OFFSET.x()) / CELL_SIZE;
    int y = (screenPos.y() - BOARD_OFFSET.y()) / CELL_SIZE;
    return QPoint(x, y);
}

QPoint MoveValidator::boardToScreen(const QPoint& boardPos) {
    // 计算屏幕坐标（中心位置）
    int x = BOARD_OFFSET.x() + boardPos.x() * CELL_SIZE + CELL_SIZE / 2;
    int y = BOARD_OFFSET.y() + boardPos.y() * CELL_SIZE + CELL_SIZE / 2;
    return QPoint(x, y);
}