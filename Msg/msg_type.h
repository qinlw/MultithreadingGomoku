#ifndef MSG_TYPE_H
#define MSG_TYPE_H

// 消息类型枚举
enum class MsgType {
    // UI -> 游戏线程
    UIMoveRequest,       // 落子请求
    UIGameStart,         // 开始游戏
    UIGameRestart,       // 重新开始
    UIGameQuit,          // 退出游戏

    // 游戏线程 -> UI
    GameStateUpdated,    // 游戏状态更新
    MoveValidated,       // 落子验证结果
    GameOver,            // 游戏结束

    // 游戏线程 -> 网络线程
    NetworkSendMove,     // 发送落子信息
    NetworkSendGameState,// 发送游戏状态
    NetworkConnect,      // 连接请求
    NetworkDisconnect,   // 断开连接

    // 网络线程 -> 游戏线程
    NetworkMoveReceived, // 收到落子信息
    NetworkConnected,    // 连接成功
    NetworkDisconnected, // 连接断开
    NetworkError,        // 网络错误

    // 资源线程相关
    ResourceLoadRequest, // 资源加载请求
    ResourceLoaded       // 资源加载完成
};

#endif // MSG_TYPE_H