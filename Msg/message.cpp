#include "message.h"

// 消息基类实现（纯虚类无需额外实现，此处补充派生类的扩展）
MoveRequestMsg::MoveRequestMsg(QPoint pos, PieceColor color)
    : Message(MsgType::UIMoveRequest), m_pos(pos), m_color(color) {
}

QPoint MoveRequestMsg::pos() const { return m_pos; }
PieceColor MoveRequestMsg::color() const { return m_color; }

GameStateMsg::GameStateMsg(GameStatus status, const QPoint& lastMove)
    : Message(MsgType::GameStateUpdated), m_status(status), m_lastMove(lastMove) {
}

GameStatus GameStateMsg::status() const { return m_status; }
QPoint GameStateMsg::lastMove() const { return m_lastMove; }