#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdarg.h>
#include "Controller.h"

class Display {
 public:
  static void print(int row, const char* format, ...);

 private:
};
#endif