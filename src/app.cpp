#include "app.h"
#include "EtRobocon2019.h"

// 演習用のユーティリティ

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused) {
  EtRobocon2019::start();
  ext_tsk();
}
// end::main_task_2[]



