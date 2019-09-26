#include "app.h"
#include "EtRobocon2019.h"
#include "Bluetooth.h"
#include <array>

// 演習用のユーティリティ

std::array<char, 256> Bluetooth::commands;

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
    Display::print(6, "BT: %d", receiveCommand);
    if(receiveCommand == 0) {
      bluetooth.serialSend(1);
      break;
    }
    // Display::print(12, "%d", debug_count);
    // debug_count += 1;
    tslp_tsk(4);
  }
  Display::print(6, "success: connect BT");

  // コマンドの受信開始
  receiveCommand = static_cast<char>(bluetooth.serialRead());
  Display::print(6, "BT: %c", receiveCommand);
  std::array<char, 256> commands;

  for(int i = 0; i < 256; i++) {
    receiveCommand = static_cast<char>(bluetooth.serialRead());
    Display::print(6, "BT: %c", receiveCommand);

    if(receiveCommand == '#') {
      break;
    }
    commands[i] = static_cast<char>(receiveCommand);
    tslp_tsk(4);
  }
  Bluetooth::commands = commands;
}
