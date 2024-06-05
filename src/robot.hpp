// Robot.hpp
#ifndef ROBOT_H  // 宏定义，防止头文件被多次包含
#define ROBOT_H

#include <sapi.h>  // 包含 SAPI 头文件

#include <ctime>
#include <mutex>
#include <string>
#include <vector>
class robot {
 private:
  struct Task {
    std::wstring message;   // 接受的信息
    std::time_t timestamp;  // 使用 time_t 类型表示时间戳
  };

  std::mutex mutex_;  // 互斥锁成员变量
  ISpVoice* pVoice = NULL;
  std::wstring speechText;  // 达芬奇根据message讲的话
  std::vector<Task> tasks;  // 用vector储存任务列表

 public:
  void speak();  // speak函数的声明
  void run();    // 检查任务并播报
  void recieveMessage(const std::wstring& message,
                      std::time_t timestamp);  // recieveMessage函数
  robot();                                     // 构造函数的声明
  ~robot();                                    // 析构函数的声明
};

#endif  // ROBOT_H