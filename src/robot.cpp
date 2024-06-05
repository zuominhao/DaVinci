// robot.cpp
#include "robot.hpp"

#include <chrono>
#include <iostream>
#include <thread>
/**构造函数
 * 初始化com库，创建声音的实例
 */
robot::robot() {
  std::cout << "正在初始化 COM 库..." << std::endl;
  HRESULT hr = ::CoInitialize(NULL);
  if (FAILED(hr)) {
    std::cerr << "Failed to initialize COM library. HRESULT: " << std::hex << hr
              << std::endl;
    return;
  }
  std::cout << "初始化 COM 库 成功！" << std::endl;
  std::cout << "正在创建声音实例..." << std::endl;
  hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice,
                        (void**)&pVoice);
  if (FAILED(hr)) {
    std::cerr << "Failed to create SpVoice instance. HRESULT: " << std::hex
              << hr << std::endl;
    pVoice = NULL;
    return;
  }
  std::cout << "声音实例创建成功!" << std::endl;
}
// 析构函数
robot::~robot() {
  std::cout << "Releasing SpVoice instance..." << std::endl;
  if (pVoice) {
    pVoice->Release();
  }
  std::cout << "Uninitializing COM library..." << std::endl;
  ::CoUninitialize();
  std::cout << "COM library uninitialized successfully." << std::endl;
}

// speak函数，用来语音播报当前需要做的事
void robot::speak() {
  if (pVoice && !speechText.empty()) {
    std::cout << "1" << std::endl;
    std::lock_guard<std::mutex> lock(mutex_);
    HRESULT hr = pVoice->Speak(speechText.c_str(), 0, NULL);  // 使用 speechText
    std::cout << "2" << std::endl;
  }
}

// recieveMessage函数，接受需要speak的信息
void robot::recieveMessage(const std::wstring& message, std::time_t timestamp) {
  Task task;
  task.message = message;
  task.timestamp = timestamp;
  tasks.push_back(task);  // 将任务添加到任务列表中
  speechText = task.message;
}
// 启动 检查任务并播报的函数
void robot::run() {
  while (true) {
    auto now = std::time(nullptr);
    for (auto it = tasks.begin(); it != tasks.end();) {
      if (now >= it->timestamp) {
        speechText = it->message;
        speak();
        it = tasks.erase(it);
      } else {
        ++it;
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 每秒检查一次
  }
}
