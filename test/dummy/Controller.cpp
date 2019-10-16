#include "Controller.h"

#include "Bluetooth.h"

std::array<char, 256> Bluetooth::commands;
bool Bluetooth::is_start = false;
std::array<Color, 10> Controller::colorBuffer = {Color::white};
int Controller::colorBufferCounter = 0;