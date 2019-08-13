#include "app.h"
#include "EtRobocon2019.h"
#include "Bluetooth.h"

// 演習用のユーティリティ

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused)
{
  while(1) {
    Display::print(1, "%d", debug_counts);
    tslp_tsk(1000);
  }
  ext_tsk();
}
// end::main_task_2[]

void bt_task(intptr_t unused)
{
  // int debug_count = 0;
  Bluetooth bluetooth;
  // Display display;
  int receiveCommand;
  FILE* bt = NULL;
  // 通信開始
  bt = bluetooth.serialOpen();
  if(bt == NULL) {
    Display::print(10, "not connected");
  } else {
    Display::print(11, "Bluetooth connected");
  }

  while(1) {
    // 受信（PCからコマンドが送られるまで一生ここで止まる）
    receiveCommand = fgetc(bt);
    Display::print(6, "%d", receiveCommand);
    // Display::print(12, "%d", debug_count);
    // debug_count += 1;
  }
}
