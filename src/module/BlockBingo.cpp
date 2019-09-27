/**
 *  @file   BlockBingo.cpp
 *  @brief  ブロックビンゴで使用する動作をまとめたクラス
 *  @author Oiwane
 */
#include "BlockBingo.h"

BlockBingo::BlockBingo(Controller& controller_, int targetBrightness_)
  : controller(controller_),
    targetBrightness(targetBrightness_),
    // navigator(controller_, targetBrightness, 0.0, 0.0, 0.0),
    length(175.0),
    isFirstProcess(true),
    // 10 : 0.823, 20 : 0.29?
    pGain(0.823),
    straightPwm(10),
    spinPwm(10)
{
}

void BlockBingo::moveCircle4OfL()
{
  Navigator navigator(controller, targetBrightness);

  navigator.traceBlackLineToSpecifiedColor(Color::yellow, straightPwm, true);
  navigator.move(-65.0, straightPwm, pGain);
  navigator.spin(45.0, false, spinPwm);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, true, spinPwm);
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::moveCircle6OfL()
{
  Navigator navigator(controller, targetBrightness);

  navigator.traceBlackLineToSpecifiedColor(Color::yellow, straightPwm, true);
  navigator.move(-85.0, straightPwm);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, false);
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execSpinRight()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(90.0, true);
}

void BlockBingo::execSpinLeft()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(90.0, false);
}

void BlockBingo::execSpin180()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(180, true);
}

void BlockBingo::execStraight()
{
  Navigator navigator(controller, targetBrightness);

  navigator.move(length * 2, straightPwm, pGain);
}

void BlockBingo::execStraightDetourRight()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(90.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execStraightDetourLeft()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(90.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnRight90ExistBlock()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurnRight90UnexistBlock()
{
  Navigator navigator(controller, targetBrightness);

  navigator.move(length, straightPwm, pGain);
  this->execSpinRight();
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execTurnLeft90ExistBlock()
{
  Navigator navigator(controller, targetBrightness);

  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnLeft90UnexistBlock()
{
  Navigator navigator(controller, targetBrightness);

  navigator.move(length, straightPwm, pGain);
  this->execSpinLeft();
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execTurn180()
{
  this->execSpin180();
  this->execStraight();
}

void BlockBingo::execTurn180DetourRight()
{
  Navigator navigator(controller, targetBrightness);

  this->execSpin180();
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  this->execSpinLeft();
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurn180DetourLeft()
{
  Navigator navigator(controller, targetBrightness);

  this->execSpin180();
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  this->execSpinRight();
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execPut()
{
  Navigator navigator(controller, targetBrightness);

  // if(isFirstProcess) {
  //   navigator.move(length, straightPwm, pGain);
  //   isFirstProcess = false;
  // }
  // navigator.move(100.0, straightPwm, pGain);
  // navigator.move(-100.0, straightPwm, pGain);
  navigator.move(-length, straightPwm, pGain);
}

void BlockBingo::execSpinRight45()
{
  Navigator navigator(controller, targetBrightness);
  navigator.spin(45.0, true);
}

void BlockBingo::execSpinLeft45()
{
  Navigator navigator(controller, targetBrightness);
  navigator.spin(45.0, false);
}

void BlockBingo::execSpinRight135()
{
  Navigator navigator(controller, targetBrightness);
  navigator.spin(135.0, true);
}

void BlockBingo::execSpinLeft135()
{
  Navigator navigator(controller, targetBrightness);
  navigator.spin(135.0, false);
}

void BlockBingo::execMoveNode()
{
  Navigator navigator(controller, targetBrightness);
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execMoveDiagonal()
{
  Navigator navigator(controller, targetBrightness);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm);
}