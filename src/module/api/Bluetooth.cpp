/**
 *  @file   Bluetooth.cpp
 *  @brief  PCとEV3がBluetooth通信するときに使う構造体
 *  @author Tatsumi0000
 */
#include "Bluetooth.h"

Bluetooth::Bluetooth() : bt(NULL) {}

Bluetooth::~Bluetooth()
{
  Bluetooth::serialClose();
}

void Bluetooth::serialOpen()
{
  bt = ev3_serial_open_file(EV3_SERIAL_BT);
  if(bt == NULL) {
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
