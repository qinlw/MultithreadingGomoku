#include "utils.h"
#include "define.h"
#include <QDebug>
#include <ctime>

namespace Utils {
    QPoint screenToBoard(int screenX, int screenY) {
        int x = (screenX - BOARD_OFFSET.x()) / CELL_SIZE;
        int y = (screenY - BOARD_OFFSET.y()) / CELL_SIZE;
        return QPoint(x, y);
    }

    QPoint boardToScreen(int boardX, int boardY) {
        int x = BOARD_OFFSET.x() + boardX * CELL_SIZE + CELL_SIZE / 2;
        int y = BOARD_OFFSET.y() + boardY * CELL_SIZE + CELL_SIZE / 2;
        return QPoint(x, y);
    }

    void logInfo(const std::string& message) {
        std::string log = "[" + getTimestamp() + "][INFO] " + message;
        qDebug() << stdStringToQString(log);
    }

    void logError(const std::string& message) {
        std::string log = "[" + getTimestamp() + "][ERROR] " + message;
        qDebug() << stdStringToQString(log);
    }

    std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::ctime(&time);
        std::string ts = ss.str();
        ts.pop_back(); // 移除换行符
        return ts;
    }

    std::string qstringToStdString(const QString& qstr) {
        return qstr.toStdString();
    }

    QString stdStringToQString(const std::string& str) {
        return QString::fromStdString(str);
    }
}