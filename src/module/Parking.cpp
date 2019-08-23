/**
 * @file Parking.cpp
 * @brief ガレージ駐車に使用するクラス
 * @author Oiwane
 */
#include "Parking.h"

Parking::Parking(Controller& controller_) : controller(controller_) {}

void Parking::parkAtAL()
{
  Navigator navigator(controller);

  navigator.moveToSpecifiedColor(Color::green, 10);
  controller.speakerPlayToneFS6(100);
  navigator.move(100, 10, 0.6);
  controller.speakerPlayToneFS6(100);
  navigator.moveToSpecifiedColor(Color::blue, 10);
  controller.speakerPlayToneFS6(100);
  navigator.move(300, 10, 0.6);
  controller.speakerPlayToneFS6(100);
  navigator.spin(90.0);

  this->stopFor3sec();
}

void Parking::parkAtAR()
{
  Navigator navigator(controller);

  navigator.moveToSpecifiedColor(Color::blue, 10);
  controller.speakerPlayToneFS6(100);
  navigator.move(250, 10, 0.6);
  controller.speakerPlayToneFS6(100);
  navigator.spin(90, false);
  controller.speakerPlayToneFS6(100);
  navigator.moveToSpecifiedColor(Color::black, 10);
  controller.speakerPlayToneFS6(100);
  navigator.move(50, 10, 0.6);
  controller.speakerPlayToneFS6(100);
  navigator.spin(90);
  controller.speakerPlayToneFS6(100);
  navigator.moveToSpecifiedColor(Color::black, 10);
  controller.speakerPlayToneFS6(100);
  navigator.moveToSpecifiedColor(Color::blue, 10);
  controller.speakerPlayToneFS6(100);
  navigator.move(125, 10, 0.6);
  controller.speakerPlayToneFS6(100);
  navigator.spin(90, false);
  controller.speakerPlayToneFS6(100);
  navigator.move(400, 10, 0.6);

  this->stopFor3sec();
}

void Parking::stopFor3sec()
{
  for(int i = 0; i < 2; i++) {
    controller.speakerPlayToneFS6(100);
    controller.tslpTsk(1000);
  }
  controller.speakerPlayToneFS6(1000);
}