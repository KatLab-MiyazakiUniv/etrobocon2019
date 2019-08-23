/**
 *  @file   Bluetooth.cpp
 *  @brief  PCとEV3がBluetooth通信する（使う時は別タスクにしたほうがいい）
 *  @author Tatsumi0000
 */
#include "Bluetooth.h"

Bluetooth::Bluetooth() : bt(nullptr)
{
  // 通信開始
  serialOpen();
}

Bluetooth::~Bluetooth()
{
  serialClose();
}

void Bluetooth::serialOpen()
{
  bt = ev3_serial_open_file(EV3_SERIAL_BT);
  // nullptrの場合
  if(!bt) {
    Display::print(10, "not connected");
  } else {
    Display::print(10, "Bluetooth connected");
  }
}

int Bluetooth::serialRead()
{
  return fgetc(bt);
}

void Bluetooth::serialClose()
{
  fclose(bt);
}
