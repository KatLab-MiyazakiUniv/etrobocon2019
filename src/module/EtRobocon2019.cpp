#include "EtRobocon2019.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"

void EtRobocon2019::start() {
  Controller controller;
  Calibrator calibrator(controller);

  calibrator.calibration();
}
