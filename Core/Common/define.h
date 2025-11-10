#ifndef DEFINE_H
#define DEFINE_H

#include <QPoint>

// 棋盘常量
const int BOARD_SIZE = 15;          // 15x15棋盘
const int CELL_SIZE = 40;           // 每个格子像素大小
const QPoint BOARD_OFFSET(50, 50);  // 棋盘左上角偏移量

// 网络常量
const int SERVER_PORT = 12345;
const QString DEFAULT_SERVER_IP = "127.0.0.1";

// 资源路径
const QString RESOURCE_PATH = ":/resource/";
const QString BLACK_PIECE_PATH = RESOURCE_PATH + "black.png";
const QString WHITE_PIECE_PATH = RESOURCE_PATH + "white.png";
const QString BOARD_IMAGE_PATH = RESOURCE_PATH + "board.png";

#endif // DEFINE_H