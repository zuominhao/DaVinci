#include "robot.hpp"

int main(int argc, char* argv[]) {
  robot DaVinci;

  // 设置两个任务，假设时间戳是未来的某个时间
  std::time_t now = std::time(nullptr);
  DaVinci.recieveMessage(L"任务1:你好，世界！", now + 1);  // 10秒后播报
  DaVinci.recieveMessage(L"任务2:再见，世界！", now + 4);  // 20秒后播报

  // 启动任务
  DaVinci.run();
  return 0;
}
