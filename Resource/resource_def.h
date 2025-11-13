#ifndef RESOURCE_DEF_H
#define RESOURCE_DEF_H

#include <QString>

// 资源类型枚举
enum class ResourceType {
    Image,  // 图片资源
    Sound   // 音效资源（预留）
};

// 图片资源ID
enum class ImageId {
    Board,      // 棋盘背景
    BlackPiece, // 黑棋
    WhitePiece, // 白棋
    ButtonStart // 开始按钮（示例）
};

// 资源路径映射
namespace ResourcePath {
    const QString Board = ":/resource/board.png";
    const QString BlackPiece = ":/resource/black.png";
    const QString WhitePiece = ":/resource/white.png";
    const QString ButtonStart = ":/resource/start_btn.png";
}

#endif // RESOURCE_DEF_H