/**
 *  @file   MoveDirectGarage
 *  @brief  ビンゴを行わずにガレージに向かうクラス
 *  @author match97
 */

//このクラスが使用されないことを願う

#include "MoveDirectGarage.h"

MoveDirectGarage::MoveDirectGarage(Controller& controller_, int targetBrightness_)
  : controller(controller_), targetBrightness(targetBrightness_)
{
}

void MoveDirectGarage::moveDirectGarageL()
{
  Navigator navigator(controller, targetBrightness);

  //ブロックを押す
  navigator.moveToSpecifiedColor(Color::yellow, 10);
  navigator.move(-60, 10);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  // 4のとこ
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(30, 10);
  navigator.spin(45.0, true);
  //ブロックを押す
  navigator.moveToSpecifiedColor(Color::red, 10);
  navigator.move(-60, 10);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(65, 10);
  navigator.spin(45.0, false);
  //真ん中
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.move(30, 10);
  navigator.spin(90.0, true);
  navigator.moveToSpecifiedColor(Color::green, 10);
  navigator.move(-60, 8);
  navigator.spin(45.0, false);
  //５のとこ
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.move(20, 10);
  navigator.spin(45.0, false);
  //以下はparkingクラスを使用
}

void MoveDirectGarage::moveDirectGarageR()
{
  Navigator navigator(controller, targetBrightness);

  navigator.moveToSpecifiedColor(Color::yellow, 10);
  // 5のとこ
  navigator.move(120, 10);
  navigator.moveToSpecifiedColor(Color::yellow, 10);
  navigator.move(-60, 10);
  navigator.spin(45.0, true);
  // navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(190, 10);
  navigator.move(60, 10);
  navigator.spin(45.0, false);
  //真ん中
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.move(25, 10);
  navigator.spin(90.0, true);
  navigator.moveToSpecifiedColor(Color::blue, 10);
  navigator.move(-60, 10);
  navigator.spin(45.0, false);
  // 4のとこ
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.moveToSpecifiedColor(Color::white, 10);
  navigator.move(30, 10);
  navigator.spin(40.0, false);
  //以下はparkingクラスを使用
}
