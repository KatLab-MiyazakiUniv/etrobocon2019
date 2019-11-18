/**
 *  @file   BlockBingo.cpp
 *  @brief  ブロックビンゴで使用する動作をまとめたクラス
 *  @author Oiwane
 */
#include "BlockBingo.h"

BlockBingo::BlockBingo(Controller& controller_, int targetBrightness_, bool isLeft_)
  : controller(controller_),
    navigator(controller_, targetBrightness),
    targetBrightness(targetBrightness_),
    isLeft(isLeft_),
    lineTracePGain(0.35),
    straightPwm(15),
    isFirstProcess(true)
{
}

void BlockBingo::execEnterBingoAreaL4()
{
  navigator.lineTraceToSpecifiedColor(Color::yellow, straightPwm, lineTracePGain, isLeft);
  controller.tslpTsk(100);
  navigator.move(-95.0, straightPwm);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(45.0, false);
  navigator.lineTraceToSpecifiedColor(Color::red, straightPwm, lineTracePGain, isLeft);
  controller.tslpTsk(100);
  navigator.move(-97.5, straightPwm);
  navigator.spin(90.0, true);
  navigator.move(lengthCrossCircleMidpoint, straightPwm);
}

void BlockBingo::execEnterBingoAreaL6()
{
  navigator.lineTraceToSpecifiedColor(Color::yellow, straightPwm, lineTracePGain, isLeft);
  controller.tslpTsk(100);
  navigator.move(-100.0, straightPwm);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(45.0, true);
  navigator.lineTraceToSpecifiedColor(Color::yellow, straightPwm, lineTracePGain, isLeft);
  controller.tslpTsk(100);
  navigator.move(-72.5, straightPwm);
  navigator.spin(90.0, false);
  navigator.move(lengthCrossCircleMidpoint, straightPwm);
}

void BlockBingo::execEnterBingoAreaR5()
{
  navigator.lineTraceToSpecifiedColor(Color::yellow, 5, 0.10);
  navigator.move(40, 15);
  navigator.steer(170 / 2 * M_PI + 38.0, 15, -1.0 / 170.0, 30.0, 0, 0);
  controller.tslpTsk(300);
  navigator.spin(90, false);

}

void BlockBingo::execEnterBingoAreaR8()
{
  navigator.lineTraceToSpecifiedColor(Color::yellow, 5, 0.10);
  navigator.move(40, 15);
  navigator.steer(170 / 2 * M_PI + 38.0, 15, 1.0 / 170.0, 30.0, 0, 0);
  controller.tslpTsk(300);
  navigator.spin(93, true);
  navigator.move(10, 15);
}

void BlockBingo::execSpinRight()
{
  this->moveCrossCircle();
  navigator.spin(90.0, true);
}

void BlockBingo::execSpinLeft()
{
  this->moveCrossCircle();
  navigator.spin(90.0, false);
}

void BlockBingo::execSpin180()
{
  this->moveCrossCircle();
  navigator.spin(180, true);
}

void BlockBingo::execStraight()
{
  navigator.move(lengthCrossCircleMidpoint * 2, 10);
}

void BlockBingo::execStraightDetourRight()
{
  navigator.move(-90.0, straightPwm);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(90.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(45.0, true);
}

void BlockBingo::execStraightDetourLeft()
{
  navigator.move(-90.0, straightPwm);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(90.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnRight90ExistBlock()
{
  navigator.move(-75.0, straightPwm);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurnRight90UnexistBlock()
{
  controller.resetMotorCount();

  Distance distance;
  constexpr double goalDistance = 70.0 * M_PI;
  while(distance.calculate(controller.getLeftMotorCount())
            - distance.calculate(controller.getRightMotorCount())
        < goalDistance) {
    controller.setLeftMotorPwm(30);
    controller.setRightMotorPwm(isLeft ? 2 : 0);
    controller.tslpTsk(4);
  }
  navigator.lineTrace(30.0, 5, 0.30, isLeft);
  navigator.lineTrace(50.0, straightPwm, 0.30, isLeft);
}

void BlockBingo::execTurnLeft90ExistBlock()
{
  navigator.move(-75.0, straightPwm);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnLeft90UnexistBlock()
{
  controller.resetMotorCount();

  Distance distance;
  constexpr double goalDistance = 70.0 * M_PI;
  while(distance.calculate(controller.getRightMotorCount())
            - distance.calculate(controller.getLeftMotorCount())
        < goalDistance) {
    controller.setRightMotorPwm(30);
    controller.setLeftMotorPwm(isLeft ? 0 : 3);
    controller.tslpTsk(4);
  }
  navigator.lineTrace(30.0, 5, 0.30, isLeft);
  navigator.lineTrace(50.0, straightPwm, 0.30, isLeft);
}

void BlockBingo::execTurn180()
{
  this->execSpin180();
  navigator.move(lengthCrossCircleMidpoint, straightPwm);
}

void BlockBingo::execPut()
{
  navigator.move(80.0, straightPwm);
  navigator.move(-120.0, straightPwm);
  navigator.moveToSpecifiedColor(Color::black, -straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
  isFirstProcess = false;
}

void BlockBingo::execMoveNode()
{
  double first = 30.0;
  navigator.move(first, straightPwm);
  navigator.lineTrace(60.0, straightPwm, lineTracePGain, isLeft);
  navigator.lineTraceExcludingMonochrome(straightPwm, lineTracePGain, isLeft);
}

void BlockBingo::execQuickPutR()
{
  navigator.move(10.0, straightPwm);
  controller.setLeftMotorPwm(30);
  controller.setRightMotorPwm(8);
  controller.speakerPlayToneFS6(100);
  controller.tslpTsk(500);
  navigator.move(150.0, straightPwm);

  controller.stopMotor();
  controller.tslpTsk(300);

  navigator.move(-150.0, straightPwm);
  controller.setLeftMotorPwm(-20);
  controller.setRightMotorPwm(-7);
  controller.speakerPlayToneFS6(100);
  controller.tslpTsk(720);

  controller.stopMotor();
}

void BlockBingo::execQuickPutL()
{
  navigator.move(10.0, straightPwm);
  controller.setLeftMotorPwm(8);
  controller.setRightMotorPwm(30);
  controller.speakerPlayToneFS6(100);
  controller.tslpTsk(500);
  navigator.move(150.0, straightPwm);

  controller.stopMotor();
  controller.tslpTsk(300);

  navigator.move(-150.0, straightPwm);
  controller.setLeftMotorPwm(-7);
  controller.setRightMotorPwm(-20);
  controller.speakerPlayToneFS6(100);
  controller.tslpTsk(720);

  controller.stopMotor();
}

void BlockBingo::execPrepareToPut()
{
  navigator.move(lengthCrossCircleMidpoint, 10);
}

void BlockBingo::execStraightStraight()
{
  navigator.move(lengthCrossCircleMidpoint * 4.0, 10);
}

void BlockBingo::moveCrossCircle()
{
  if(!isFirstProcess) {
    navigator.move(90.0, straightPwm);
  }
}