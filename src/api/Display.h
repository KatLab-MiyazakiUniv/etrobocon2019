#ifndef DISPLAY_H
#define DISPLAY_H

#include "Controller.h"

class Display {
 public:
  static void print(int row, const char* format, ...);
  static void init();

 private:
};
#endif