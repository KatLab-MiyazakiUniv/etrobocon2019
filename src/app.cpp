#include "app.h"
#include "EtRobocon2019.h"
#include "Bluetooth.h"
#include "Controller.h"
#include <array>

// 演習用のユーティリティ
std::array<char, 256> Bluetooth::commands;
bool Bluetooth::is_start = false;
std::array<Color, 10> Controller::colorBuffer = { Color::black };
int Controller::colorBufferCounter = 0;

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused)
{
  // int debug_counts = 0;
  // while(1) {
  //   Display::print(1, "%d", debug_counts);
  //   tslp_tsk(1000);
  //   debug_counts++;
  // }
  EtRobocon2019::start();
  ext_tsk();
}
// end::main_task_2[]

void color_task(intptr_t unused)
{
  Controller controller;
  while(true) {
    controller.registerColor();
    controller.tslpTsk(4);
  }
  ext_tsk();
}

void bt_task(intptr_t unused)
{
  // int debug_count = 0;
  Bluetooth bluetooth;
  int receiveCommand;
  Controller controller;

  while(1) {
    // 受信（PCからコマンドが送られるまで一生ここで止まる）
    receiveCommand = bluetooth.serialRead();
    if(receiveCommand == 0) {
      bluetooth.serialSend(1);
      break;
    }
    controller.tslpTsk(4);
  }
  Display::print(12, "success: connect BT");
  bluetooth.flush();

  // タッチセンサが押されるまで待つ
  while(!Bluetooth::is_start) {
    controller.tslpTsk(4);
  }

  // PCにスタート合図を送る
  bluetooth.serialSend(2);

  // コマンドの受信開始
  // receiveCommand = static_cast<char>(bluetooth.serialRead());
  // Display::print(9, "BT: %c", receiveCommand);
  constexpr int max_command_size = 256;
  std::array<char, max_command_size> commands;

  char command_string[max_command_size];
  int i = 0;
  for(i = 0; i < max_command_size; i++) {
    receiveCommand = static_cast<char>(bluetooth.serialRead());
    Display::print(9, "BT: %c", receiveCommand);

    if(receiveCommand == '#') {
      break;
    }
    command_string[i] = commands[i] = receiveCommand;
    controller.tslpTsk(4);
  }
  Bluetooth::commands = commands;
  command_string[i + 1] = '\0';
  Display::print(10, "Commands: %-10s", command_string);

  ext_tsk();
}
