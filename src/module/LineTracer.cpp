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
    turnControl(targetBrightness_, 0.0, 0.0, 0.0)
{
  //  Logger logger{ "dataw.csv" };
  //  logger << "Distance"<< "speed";
}

void LineTracer::run(const NormalCourseProperty& settings)
{
  // 関数呼び出し時の走行距離を取得・設定
  int initialDistance
      = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

  int currentDistance = initialDistance;                   // 現在の走行距離
  int turnValue = 0;                                       // 旋回値
  int speedValue = 0;                                      // 直進値
  int leftPWM = 0;                                         // 左モータの出力
  int rightPWM = 0;                                        // 右モータの出力
  Curvature curvature(settings.curvature, 1.2, 1.8, 0.0);  // 曲率PID制御
  constexpr int baseSpeedRate = 640 / 70;  // PWM70で640mm/secとしたときの速度比
  // Logger logger{ "a" };

  // 目標距離を走り終えるまでループ
  while(currentDistance - initialDistance < settings.targetDistance) {
    // 前進値の計算
    speedValue = settings.targetSpeed;

    // 旋回値の計算
    turnValue
        = turnControl.calculateTurn(speedValue, controller.getBrightness(), targetBrightness,
                                    settings.turnPid.Kp, settings.turnPid.Ki, settings.turnPid.Kd);

    // 曲率PID制御による旋回値の計算
    turnValue += curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount(),
                                   baseSpeedRate * settings.targetSpeed);

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
    // PWM値の設定
    controller.setLeftMotorPwm(leftPWM);
    controller.setRightMotorPwm(rightPWM);

    // 現在の走行距離の取得
    currentDistance
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    //  Logger logger{"dataw.csv","a"};
    //  logger << currentDistance << speedValue;
    controller.tslpTsk(4);
  }
}

void LineTracer::setTargetBrightness(int targetBrightness_)
{
  targetBrightness = targetBrightness_;
}
