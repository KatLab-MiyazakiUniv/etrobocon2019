/**
 *  @file   Bluetooth.h
 *  @brief  PCとEV3がBluetooth通信する（使う時は別タスクにしたほうがいい）
 *  @author Tatsumi0000
 */
#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include "Controller.h"
#include "Display.h"
#include <cstdio>
#include <array>

class Bluetooth {
 public:
  /**
   * コンストラクタ
   * @brief Bluetoothクラスのコンストラクタ
   */
  Bluetooth(/* args */);

  /**
   * デストラクタ
   * @brief Bluetoothクラスのデストラクタ
   */
  ~Bluetooth();

  /**
   * Bluetooth通信を開始するメソッド
   * @brief シリアル通信を開始する
   */
  void serialOpen();

  /**
   * PCからデータを読み取る
   * @brief fgetc関数を用いてデータを読み取る
   * @return 読み取ったデータ
   */
  int serialRead();

  /**
   * PCにデータを送る
   * @brief fputc関数を用いてデータを読み取る
   */
  void serialSend(int c);

  /**
   * シリアル通信を終了する
   * @brief FILEポインタを開放する（デストラクタで呼び出す）
   */
  void serialClose();

  static std::array<char, 256> commands;

 private:
  std::FILE* bt;
};

#endif
