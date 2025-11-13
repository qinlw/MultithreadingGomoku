#ifndef UTILS_H
#define UTILS_H

#include <QPoint>
#include <string>
#include <chrono>
#include <sstream>

namespace Utils {
    // 坐标转换（屏幕坐标 ↔ 棋盘坐标，补充MoveValidator未覆盖的场景）
    QPoint screenToBoard(int screenX, int screenY);
    QPoint boardToScreen(int boardX, int boardY);

    // 日志工具
    void logInfo(const std::string& message);
    void logError(const std::string& message);

    // 时间戳工具
    std::string getTimestamp();

    // 字符串转换
    std::string qstringToStdString(const QString& qstr);
    QString stdStringToQString(const std::string& str);
}

#endif // UTILS_H