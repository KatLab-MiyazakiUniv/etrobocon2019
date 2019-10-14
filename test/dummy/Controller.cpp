#include "Controller.h"

#include "Bluetooth.h"

std::array<char, 256> Bluetooth::commands;
bool Bluetooth::is_start = false;
std::array<Color, 10> Controller::color_buffer = {Color::white};
int Controller::color_buffer_counter = 0;