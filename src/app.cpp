#include "app.h"
#include "EtRobocon2019.h"
#include "Display.h"

// 演習用のユーティリティ
int debug_count = 0;
/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused)
{
  EtRobocon2019::start();
  ext_tsk();
}
// end::main_task_2[]

void bt_task(intptr_t unused)
{
  Display display;
  int receiveCommand;
  // 通信開始
  FILE* bt = ev3_serial_open_file(EV3_SERIAL_BT);
  // Bluetooth接続ができていないとここでプログラムが落ちる（確信）
  assert(bt != NULL);
  display.print(10, "Bluetooth connected");
  while(1) {
    // 受信（PCからコマンドが送られてくるまで一生ここで止まる）
    receiveCommand = fgetc(bt);
    // 送信
    fprintf(bt, "%d\r\n", debug_count);
    switch(receiveCommand) {
      case '1':
        display.print(6, "%c", receiveCommand);
        break;
      case '2':
        display.print(7, "%c", receiveCommand);
        break;
      case '3':
        display.print(8, "%c", receiveCommand);
        break;
      default:
        display.print(9, "%c", receiveCommand);
        break;
    }
    debug_count += 1;
  }
}
