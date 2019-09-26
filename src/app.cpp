#include "app.h"
#include "EtRobocon2019.h"
#include "Bluetooth.h"
#include <array>

// 演習用のユーティリティ

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

void bt_task(intptr_t unused)
{
  // int debug_count = 0;
  Bluetooth bluetooth;
  int receiveCommand;

  while(1) {
    // 受信（PCからコマンドが送られるまで一生ここで止まる）
    receiveCommand = bluetooth.serialRead();
    if(receiveCommand == 0) {
      bluetooth.serialSend(1);
      break;
    }
    tslp_tsk(4);
  }
  Display::print(12, "success: connect BT");

  // コマンドの受信開始
  //receiveCommand = static_cast<char>(bluetooth.serialRead());
  //Display::print(9, "BT: %c", receiveCommand);
  int command_size = 256;
  std::array<char, command_size> commands;

  char command_string[command_size];
  int i = 0;
  for(i = 0; i < command_size; i++) {
    receiveCommand = static_cast<char>(bluetooth.serialRead());
    Display::print(9, "BT: %c", receiveCommand);

    if(receiveCommand == '#') {
      break;
    }
    command_string[i] = commands[i] = receiveCommand;
    tslp_tsk(4);
  }
  Bluetooth::commands = commands;
  command_string[i+1] = '\0';
  Display::print(10, "Commands: %-10s", command_string);
  ext_tsk();
}
