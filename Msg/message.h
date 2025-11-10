#ifndef MESSAGE_H
#define MESSAGE_H

#include "msg_type.h"
#include <QPoint>
#include <QVariant>
#include "core/common/enums.h"

class Message {
public:
    explicit Message(MsgType type) : m_type(type) {}
    virtual ~Message() = default;

    MsgType type() const { return m_type; }

protected:
    MsgType m_type;
};

// 落子请求消息
class MoveRequestMsg : public Message {
public:
    MoveRequestMsg(QPoint pos, PieceColor color)
        : Message(MsgType::UIMoveRequest), m_pos(pos), m_color(color) {
    }

    QPoint pos() const { return m_pos; }
    PieceColor color() const { return m_color; }

private:
    QPoint m_pos;
    PieceColor m_color;
};

// 游戏状态更新消息
class GameStateMsg : public Message {
public:
    GameStateMsg(GameStatus status, const QPoint& lastMove = QPoint(-1, -1))
        : Message(MsgType::GameStateUpdated), m_status(status), m_lastMove(lastMove) {
    }

    GameStatus status() const { return m_status; }
    QPoint lastMove() const { return m_lastMove; }

private:
    GameStatus m_status;
    QPoint m_lastMove;
};

#endif // MESSAGE_H