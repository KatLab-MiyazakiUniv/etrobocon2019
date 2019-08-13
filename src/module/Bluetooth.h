/**
 *  @file   Bluetooth.h
 *  @brief  PCとEV3がBluetooth通信するときに使う構造体
 *  @author Tatsumi0000
 */
#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "Display.h"
#include "ev3api.h"

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
