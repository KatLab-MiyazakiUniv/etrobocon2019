#include "Controller.h"

#include "Bluetooth.h"

std::array<char, 256> Bluetooth::commands;
bool Bluetooth::is_start = false;