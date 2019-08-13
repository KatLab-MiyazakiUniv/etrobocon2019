/**
 *  @file   Bluetooth.cpp
 *  @brief  PCとEV3がBluetooth通信するときに使う構造体
 *  @author Tatsumi0000
 */
#include "Bluetooth.h"

Bluetooth::Bluetooth() {}

FILE* Bluetooth::serialOpen()
{
  FILE* bt = NULL;

  bt = ev3_serial_open_file(EV3_SERIAL_BT);
  if(bt == NULL) {
    Display::print(6, "failed to ev3_serial_open_file");
    return NULL;
  }
  return bt;
}
