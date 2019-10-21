/**
 *  @file   BlockBingo.cpp
 *  @brief  ブロックビンゴで使用する動作をまとめたクラス
 *  @author Oiwane
 */
#include "BlockBingo.h"

BlockBingo::BlockBingo(Controller& controller_, int targetBrightness_)
  : controller(controller_),
    navigator(controller_, targetBrightness),
    targetBrightness(targetBrightness_),
    length(175.0),
    isFirstProcess(true),
    pGain(0.823), // 10 : 0.823, 20 : 0.29?
    straightPwm(10)
{
}

void BlockBingo::moveCircle4OfL()
{
  navigator.traceBlackLineToSpecifiedColor(Color::yellow, 5, 0.10);
  navigator.move(-65.0, straightPwm, pGain);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::red, straightPwm);
  navigator.move(-72.5, straightPwm, pGain);
  navigator.spin(90.0, true);
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::moveCircle6OfL()
{
  navigator.traceBlackLineToSpecifiedColor(Color::yellow, 5, 0.10);
  navigator.move(-70.0, straightPwm);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::yellow, straightPwm);
  navigator.move(-72.5, straightPwm, pGain);
  navigator.spin(90.0, false);
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execSpinRight()
{
  navigator.spin(90.0, true);
}

void BlockBingo::execSpinLeft()
{
  navigator.spin(90.0, false);
}

void BlockBingo::execSpin180()
{
  navigator.spin(180, true);
}

void BlockBingo::execStraight()
{
  navigator.move(length * 2, straightPwm, pGain);
}

void BlockBingo::execStraightDetourRight()
{
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
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurnRight90UnexistBlock()
{
  navigator.move(length, straightPwm, pGain);
  this->execSpinRight();
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execTurnLeft90ExistBlock()
{
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnLeft90UnexistBlock()
{
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
  navigator.move(-120.0, straightPwm, pGain);
  navigator.moveToSpecifiedColor(Color::black, -straightPwm);
  navigator.move(50.0, straightPwm, pGain);
}

void BlockBingo::execSpinRight45()
{
  navigator.spin(45.0, true);
}

void BlockBingo::execSpinLeft45()
{
  navigator.spin(45.0, false);
}

void BlockBingo::execSpinRight135()
{
  navigator.spin(135.0, true);
}

void BlockBingo::execSpinLeft135()
{
  navigator.spin(135.0, false);
}

void BlockBingo::execMoveNode()
{
  navigator.move(length, straightPwm, pGain);
}

void BlockBingo::execMoveDiagonal()
{
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(50.0, straightPwm);
}