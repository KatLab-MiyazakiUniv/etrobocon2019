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
    lengthCrossCircleCenter(175.0),
    lengthColorSensorAxis(50.0),
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
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::red, straightPwm);
  navigator.move(-72.5, straightPwm, pGain);
  navigator.spin(90.0, true);
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
}

void BlockBingo::moveCircle6OfL()
{
  navigator.traceBlackLineToSpecifiedColor(Color::yellow, 5, 0.10);
  navigator.move(-70.0, straightPwm);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::yellow, straightPwm);
  navigator.move(-72.5, straightPwm, pGain);
  navigator.spin(90.0, false);
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
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
  navigator.move(lengthCrossCircleCenter * 2, straightPwm, pGain);
}

void BlockBingo::execStraightDetourRight()
{
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(90.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execStraightDetourLeft()
{
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(90.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnRight90ExistBlock()
{
  navigator.spin(45.0, true);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurnRight90UnexistBlock()
{
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
  navigator.spin(45.0, true);
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
}

void BlockBingo::execTurnLeft90ExistBlock()
{
  navigator.spin(45.0, false);
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execTurnLeft90UnexistBlock()
{
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
  navigator.spin(45.0, false);
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
}

void BlockBingo::execTurn180()
{
  this->execSpin180();
  this->execStraight();
}

void BlockBingo::execTurn180DetourRight()
{
  this->execSpin180();
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  this->execSpinRight();
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, true);
}

void BlockBingo::execTurn180DetourLeft()
{
  this->execSpin180();
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  this->execSpinRight();
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
  navigator.spin(45.0, false);
}

void BlockBingo::execPut()
{
  navigator.move(-120.0, straightPwm, pGain);
  navigator.moveToSpecifiedColor(Color::black, -straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm, pGain);
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
  navigator.move(lengthCrossCircleCenter, straightPwm, pGain);
}

void BlockBingo::execMoveDiagonal()
{
  navigator.moveToSpecifiedColor(Color::black, straightPwm);
  navigator.move(lengthColorSensorAxis, straightPwm);
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