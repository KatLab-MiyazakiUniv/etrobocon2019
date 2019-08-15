/**
 *  @file   Bluetooth.h
 *  @brief  PCとEV3がBluetooth通信する（使う時は別タスクにしたほうがいい）
 *  @author Tatsumi0000
 */
#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "Controller.h"
#include "Display.h"

class Bluetooth {
 public:
  /** コンストラクタ
   */
  Bluetooth(/* args */);

  /**
   * Bluetooth通信を開始するメソッド
   */
  FILE* serialOpen();

 private:
  /* data */
};

#endif
