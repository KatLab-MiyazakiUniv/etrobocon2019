#include "Display.h"

void Display::print(int row, const char* format, ...)
{
  va_list arg;
  char msg[32];

  va_start(arg, format);
  vsprintf(msg, format, arg);
  va_end(arg);

  const int lineHeight = 10;
  // フォントの設定
  Controller::lcdSetFont();

  Controller::lcdFillRect(0, row * lineHeight, lineHeight);
  Controller::lcdDrawString(msg, 0, row * lineHeight);
}
