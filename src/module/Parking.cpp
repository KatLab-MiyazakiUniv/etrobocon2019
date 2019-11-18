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

  navigator.move(110, 13);                                           // 200mm直進
  navigator.spin(60, false);                                         // 60度左回転
  navigator.moveToSpecifiedColor(Color::black, 13);                  // 黒詠むまで走る
  navigator.move(50, 10);                                            // 50mm前進
  navigator.spin(60, true);                                          // 55度右回転
  navigator.move(0.02, 10);                                          // 0.03mm進む
  navigator.lineTraceToSpecifiedColor(Color::blue, 20, 0.35, true);  // 左ライントレースしながら青
  navigator.move(50, 20);
  navigator.spin(90, false);      // 90度左旋回
  controller.setArmMotorPwm(40);  //アームを上に動かす
  controller.resetMotorCount();
  navigator.move(360, 25);  // 400mm前進

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