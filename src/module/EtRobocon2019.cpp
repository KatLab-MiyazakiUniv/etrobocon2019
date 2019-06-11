#include "EtRobocon2019.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "SpeedControl.h"

void EtRobocon2019::start()
{
  Controller controller;
  Calibrator calibrator(controller);

  calibrator.calibration();

  SpeedControl speedcontrol;

  int targetSpeed = 300; //[mm/s]

  double pwmValue = speedcontrol.calculateSpeed(targetSpeed, 0.6, 0.05, 0.04);

  controller.leftWheel.setPWM(pwmValue);
  controller.rightWheel.setPWM(pwmValue);

  controller.tslpTsk(1000);

  controller.leftWheel.setPWM(0.0);
  controller.rightWheel.setPWM(0.0);
}