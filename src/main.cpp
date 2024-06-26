#include <iostream>
#include <thread>

#include "robot.hpp"
int main(int argc, char* argv[]) {
  robot DaVinci;
  // 启动监控线程，用于接收用户输入的新任务
  std::thread monitorThread(&robot::monitor, &DaVinci);

  // 设置默认任务仅供测试，假设时间戳是未来的某个时间，后面会改成真实的具体时间
  std::time_t now = std::time(nullptr);
  DaVinci.recieveMessage(L"任务1:你好，世界！", now + 1);
  DaVinci.recieveMessage(L"任务2:再见，世界！", now + 15);
  DaVinci.recieveMessage(L"任务3:我又回来啦，世界！", now + 3);

  // 启动任务
  DaVinci.run();
  monitorThread.join();
  return 0;
}
