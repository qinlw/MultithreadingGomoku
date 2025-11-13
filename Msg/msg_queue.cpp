#include "msg_queue.h"

// 消息队列实现（头文件中已包含内联函数，此处补充非内联逻辑）
// 注：C++11后模板和内联函数可直接在头文件实现，此处仅作示例
MsgQueue::MsgQueue() = default;
MsgQueue::~MsgQueue() = default;

// 已在头文件中内联实现push/pop等方法，此处无需重复