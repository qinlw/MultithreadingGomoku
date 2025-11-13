#include "main_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include "../../Core/Common/utils.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_uiMsgQueue(std::make_shared<MsgQueue>()) {
    initUI();
}

MainWindow::~MainWindow() {
    // 停止线程（如果需要）
}

void MainWindow::setThreads(std::shared_ptr<GameThread> gameThread,
    std::shared_ptr<ResourceThread> resThread) {
    m_gameThread = gameThread;
    m_resThread = resThread;
    if (m_gameThread) {
        m_gameThread->setUiMsgQueue(m_uiMsgQueue);
        // 启动消息监听（可通过定时器轮询或信号槽）
        connect(&m_msgTimer, &QTimer::timeout, this, &MainWindow::onGameMessage);
        m_msgTimer.start(10); // 10ms轮询一次
    }
}

void MainWindow::initUI() {
    setWindowTitle("五子棋对战");
    setFixedSize(800, 600);

    // 主布局
    auto centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget);

    // 棋盘组件
    m_chessBoardWidget = new ChessBoardWidget(this);
    mainLayout->addWidget(m_chessBoardWidget, 3);

    // 信息面板
    m_infoPanel = new GameInfoPanel(this);
    mainLayout->addWidget(m_infoPanel, 1);

    setCentralWidget(centralWidget);
}

void MainWindow::onGameMessage() {
    std::shared_ptr<Message> msg;
    while (m_uiMsgQueue->tryPop(msg)) {
        switch (msg->type()) {
        case MsgType::GameStateUpdated: {
            auto stateMsg = static_cast<GameStateMsg*>(msg.get());
            m_chessBoardWidget->updateLastMove(stateMsg->lastMove());
            m_infoPanel->updateStatus(stateMsg->status());
            break;
        }
        case MsgType::ResourceLoaded: {
            auto resMsg = static_cast<ResourceLoadedMsg*>(msg.get());
            if (resMsg->id() == ImageId::Board) {
                m_chessBoardWidget->loadBoardImage();
            }
            break;
        }
        default:
            break;
        }
    }
}