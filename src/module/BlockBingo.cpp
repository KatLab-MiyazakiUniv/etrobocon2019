/**
 *  @file   BlockBingo.cpp
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#include "BlockBingo.h"

BlockBingo::BlockBingo(Controller& controller_)
  : controller(controller_), length(175.0), isFirstProcess(true)
{
  this->initMap();
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

void BlockBingo::execSpinRight90()
{
  Navigator navigator(controller);

  navigator.spin(90.0, true);
}

void BlockBingo::execSpinLeft90()
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
  this->execSpinRight90();
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
  this->execSpinLeft90();
  navigator.move(length, 10, 0.6);
}

void BlockBingo::execTurn180()
{
  this->execSpin180();
  this->execStraight();
}

void BlockBingo::execTurnRight180()
{
  Navigator navigator(controller);

  this->execSpin180();
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  this->execSpinLeft90();
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurnLeft180()
{
  Navigator navigator(controller);

  this->execSpin180();
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, 10);
  navigator.move(50.0, 10, 0.6);
  this->execSpinRight90();
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

void BlockBingo::initMap()
{
  mp["a"] = Order::ENTER_BINGO_AREA_L4;
  mp["b"] = Order::ENTER_BINGO_AREA_L6;
  mp["c"] = Order::STRAIGHT;
  mp["d"] = Order::SPIN_RIGHT90;
  mp["e"] = Order::SPIN_LEFT90;
  mp["f"] = Order::SPIN180;
  mp["g"] = Order::PUT;

  mp["h"] = Order::STRAIGHT_DETOUR_RIGHT;
  mp["i"] = Order::STRAIGHT_DETOUR_LEFT;
  mp["j"] = Order::TURN_RIGHT90_EXIST_BLOCK;
  mp["k"] = Order::TURN_RIGHT90_UNEXIST_BLOCK;
  mp["l"] = Order::TURN_LEFT90_EXIST_BLOCK;
  mp["m"] = Order::TURN_LEFT90_UNEXIST_BLOCK;
  mp["n"] = Order::TURN180;
  mp["o"] = Order::TURN_RIGHT180;
  mp["p"] = Order::TURN_LEFT180;
}