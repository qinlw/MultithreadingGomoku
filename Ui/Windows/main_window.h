#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "../Widgets/chess_board_widget.h"
#include "../Widgets/game_info_panel.h"
#include "../../Thread/game_thread.h"
#include "../../Thread/resource_thread.h"
#include "../../Msg/msg_queue.h"
#include <memory>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    // 设置游戏线程和资源线程
    void setThreads(std::shared_ptr<GameThread> gameThread,
        std::shared_ptr<ResourceThread> resThread);

private slots:
    // 处理来自游戏线程的消息
    void onGameMessage();

private:
    void initUI();
    void connectSignals();

    ChessBoardWidget* m_chessBoardWidget; // 棋盘组件
    GameInfoPanel* m_infoPanel;           // 信息面板

    std::shared_ptr<GameThread> m_gameThread;
    std::shared_ptr<ResourceThread> m_resThread;
    std::shared_ptr<MsgQueue> m_uiMsgQueue; // UI线程消息队列
};

#endif // MAIN_WINDOW_H