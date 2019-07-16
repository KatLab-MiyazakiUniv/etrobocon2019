/**
 *  @file   Bluetooth.cpp
 *  @brief  Bluetooth通信をする
 *  @author Tatsumi0000
 */
#include "Bluetooth.h"

Bluetooth::Bluetooth() : size(0) {}

void Bluetooth::receiveMessage()
{
  size = serial_rea_dat(SIO_PORT_BT, message, 8);
}

int Bluetooth::getSize() const
{
  return size;
}
