#include "chess_board.h"

ChessBoard::ChessBoard(int size) : m_size(size) {
    reset();
}

void ChessBoard::reset() {
    m_board.assign(m_size, std::vector<PieceColor>(m_size, PieceColor::None));
    m_lastMove = QPoint(-1, -1);
}

PieceColor ChessBoard::getPiece(int x, int y) const {
    if (isValidPosition(x, y)) {
        return m_board[x][y];
    }
    return PieceColor::None;
}

PieceColor ChessBoard::getPiece(const QPoint& pos) const {
    return getPiece(pos.x(), pos.y());
}

bool ChessBoard::placePiece(int x, int y, PieceColor color) {
    if (!isValidPosition(x, y) || m_board[x][y] != PieceColor::None) {
        return false;
    }

    m_board[x][y] = color;
    m_lastMove = QPoint(x, y);
    return true;
}

bool ChessBoard::placePiece(const QPoint& pos, PieceColor color) {
    return placePiece(pos.x(), pos.y(), color);
}

bool ChessBoard::isValidPosition(int x, int y) const {
    return x >= 0 && x < m_size && y >= 0 && y < m_size;
}

bool ChessBoard::isValidPosition(const QPoint& pos) const {
    return isValidPosition(pos.x(), pos.y());
}