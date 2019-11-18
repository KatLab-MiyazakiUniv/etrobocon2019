/**
 * @file Parking.cpp
 * @brief ガレージ駐車に使用するクラス
 * @author Oiwane
 * updated by match97
 */
#include "Parking.h"

Parking::Parking(Controller& controller_, int targetBrightness_)
  : controller(controller_), targetBrightness(targetBrightness_)
{
}

void Parking::parkAtAL()
{
  Navigator navigator(controller, targetBrightness);

  navigator.moveToSpecifiedColor(Color::green, 10);
  navigator.move(100, 10);
  navigator.spin(10.0, false);
  navigator.moveToSpecifiedColor(Color::blue, 10);
  navigator.spin(10.0, true);
  navigator.move(300, 10);
  navigator.spin(90.0, false);

  this->stopFor3sec();
}

void Parking::parkAtAR()
{
  Navigator navigator(controller, targetBrightness);

  navigator.moveToSpecifiedColor(Color::blue, 10);
  navigator.move(250, 10);
  navigator.spin(40, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(40, 10);
  navigator.spin(45, true);
  navigator.moveToSpecifiedColor(Color::blue, 10);
  navigator.move(130, 10);
  navigator.spin(90, false);
  navigator.move(400, 10);

  this->stopFor3sec();
}

void Parking::stopFor3sec()
{
  for(int i = 0; i < 3; i++) {
    controller.speakerPlayToneFS6(100);
    controller.tslpTsk(1000);
  }
  controller.speakerPlayToneFS6(1000);
}