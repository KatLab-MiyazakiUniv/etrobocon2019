/**
 *  @file   BlockBingo.cpp
 *  @brief  ブロックビンゴで使用する動作をまとめたクラス
 *  @author Oiwane
 */
#include "BlockBingo.h"

BlockBingo::BlockBingo(Controller& controller_)
  : controller(controller_), length(175.0), isFirstProcess(true)
{
}

void BlockBingo::moveCircle4OfL()
{
  Navigator navigator(controller);

  navigator.moveToSpecifiedColor(Color::yellow, 10);
  navigator.move(-65.0, 10, 0.6);
  navigator.spin(45.0, false, 10);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, true, 10);
  navigator.move(length, 10, 0.6);
}

void BlockBingo::moveCircle6OfL()
{
  Navigator navigator(controller);

  navigator.moveToSpecifiedColor(Color::yellow, 10);
  navigator.move(-65.0, 10);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, false);
  navigator.move(length, 10, 0.6);
}

void BlockBingo::execSpinRight()
{
  Navigator navigator(controller);

  navigator.spin(90.0, true);
}

void BlockBingo::execSpinLeft()
{
  Navigator navigator(controller);

  navigator.spin(90.0, false);
}

void BlockBingo::execSpin180()
{
  Navigator navigator(controller);

  navigator.spin(180, true);
}

void BlockBingo::execStraight()
{
  Navigator navigator(controller);

  navigator.move(length * 2, 10, 0.6);
}

void BlockBingo::execStraightDetourRight()
{
  Navigator navigator(controller);

  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(90.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, true);
}

void BlockBingo::execStraightDetourLeft()
{
  Navigator navigator(controller);

  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(90.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnRight90ExistBlock()
{
  Navigator navigator(controller);

  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurnRight90UnexistBlock()
{
  Navigator navigator(controller);

  navigator.move(length, 10, 0.6);
  this->execSpinRight();
  navigator.move(length, 10, 0.6);
}

void BlockBingo::execTurnLeft90ExistBlock()
{
  Navigator navigator(controller);

  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnLeft90UnexistBlock()
{
  Navigator navigator(controller);

  navigator.move(length, 10, 0.6);
  this->execSpinLeft();
  navigator.move(length, 10, 0.6);
}

void BlockBingo::execTurn180()
{
  this->execSpin180();
  this->execStraight();
}

void BlockBingo::execTurn180DetourRight()
{
  Navigator navigator(controller);

  this->execSpin180();
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  this->execSpinLeft();
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurn180DetourLeft()
{
  Navigator navigator(controller);

  this->execSpin180();
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  this->execSpinRight();
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, false);
}

void BlockBingo::execPut()
{
  Navigator navigator(controller);

  if(isFirstProcess) {
    navigator.move(length, 10, 0.6);
    isFirstProcess = false;
  }
  navigator.move(100.0, 10, 0.6);
  navigator.move(-100.0, 10, 0.6);
}
