#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../common/enums.h"
#include "../common/define.h"
#include <vector>
#include <QPoint>

class ChessBoard {
public:
    ChessBoard(int size = BOARD_SIZE);

    // 重置棋盘
    void reset();

    // 获取指定位置的棋子
    PieceColor getPiece(int x, int y) const;
    PieceColor getPiece(const QPoint& pos) const;

    // 放置棋子
    bool placePiece(int x, int y, PieceColor color);
    bool placePiece(const QPoint& pos, PieceColor color);

    // 检查位置是否有效
    bool isValidPosition(int x, int y) const;
    bool isValidPosition(const QPoint& pos) const;

    // 获取棋盘大小
    int size() const { return m_size; }

    // 获取最后落子位置
    QPoint lastMove() const { return m_lastMove; }

private:
    int m_size;                          // 棋盘大小
    std::vector<std::vector<PieceColor>> m_board; // 棋盘数据
    QPoint m_lastMove;                   // 最后落子位置
};

#endif // CHESS_BOARD_H