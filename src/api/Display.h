#ifndef __DISPLAY__
#define __DISPLAY__

#include "Controller.h"

class Display {
 public:
  static void print(int row, const char* format, ...);
  static void init();

 private:
};
#endif