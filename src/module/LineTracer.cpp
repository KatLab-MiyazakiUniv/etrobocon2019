/**
 *  @file   LineTracer.cpp
 *  @brief  ライントレースを行うクラス
 *  @author Takahiro55555
 */

#include "LineTracer.h"
#include "Logger.h"

LineTracer::LineTracer(Controller& controller_, int targetBrightness_, bool isLeftCourse_)
  : controller(controller_),
    targetBrightness(targetBrightness_),
    isLeftCourse(isLeftCourse_),
    distance(),
    speedControl(controller, 0.0, 0.0, 0.0, 0.0),
    turnControl(targetBrightness_, 0.0, 0.0, 0.0)
{
  Logger logger{ "w" };
  logger << "brightness"
         << "speed"
         << "turn"
         << "LEFT"
         << "RIGHT";
}

void LineTracer::run(NormalCourseProperty& settings)
{
  // 関数呼び出し時の走行距離を取得・設定
  int initialDistance
      = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

  int currentDistance = initialDistance;  // 現在の走行距離
  int turnValue = 0;                      // 旋回値
  int speedValue = 0;                     // 直進値
  int leftPWM = 0;                        // 左モータの出力
  int rightPWM = 0;                       // 右モータの出力
  Logger logger{ "a" };

  // 目標距離を走り終えるまでループ
  while(currentDistance - initialDistance < settings.targetDistance) {
    // 前進値の計算
    speedValue = speedControl.calculateSpeed(settings.targetSpeed, settings.speedPid.Kp,
                                             settings.speedPid.Ki, settings.speedPid.Kd);

    // 旋回値の計算
    turnValue
        = turnControl.calculateTurn(speedValue, controller.getBrightness(), targetBrightness,
                                    settings.turnPid.Kp, settings.turnPid.Ki, settings.turnPid.Kd);

    // モータ出力の計算
    if(isLeftCourse) {
      // Leftコースの場合
      leftPWM = speedValue - turnValue;
      rightPWM = speedValue + turnValue;
    } else {
      // Rightコースの場合
      leftPWM = speedValue + turnValue;
      rightPWM = speedValue - turnValue;
    }
    logger << controller.getBrightness() << speedValue << turnValue << leftPWM << rightPWM;
    // PWM値の設定
    controller.setLeftMotorPwm(leftPWM);
    controller.setRightMotorPwm(rightPWM);

    // 現在の走行距離の取得
    currentDistance
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    controller.tslpTsk(4);
  }
}

void LineTracer::setTargetBrightness(int targetBrightness_)
{
  targetBrightness = targetBrightness_;
}
