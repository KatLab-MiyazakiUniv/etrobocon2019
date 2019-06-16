/**
 *  @file   LineTracer.cpp
 *  @brief  ライントレースを行うクラス
 *  @author Takahiro55555
 */

#include "LineTracer.h"

/** コンストラクタ
 *  @param targetBrightness_  [カラーセンサーの目標値]
 *  @param isLeftCourse_ [Leftコースである場合True]
 */
LineTracer::LineTracer(int targetBrightness_, bool isLeftCourse_)
    : targetBrightness(targetBrightness_),
      isLeftCourse(isLeftCourse_) {}

/** 指定された距離だけ走行する。
 *  @bfief 走行距離や目標スピード、スピード制御PID、回転制御PIDを NormalCourseProperty 構造体を使用し渡す。
 *  @param settings [各種パラメータが入っている NormalCourseProperty 構造体]
 */
void LineTracer::run(NormalCourseProperty &settings)
{
    // 関数呼び出し時の走行距離を取得・設定
    int initialDistance = distance.getDistance(
        controller.getLeftMotorCount(), controller.getRightMotorCount());

    int currentDistance = initialDistance; // 現在の走行距離
    int turnValue = 0;                     // 旋回値
    int speedValue = 0;                    // 直進値
    int leftPWM = 0;                       // 左モータの出力
    int rightPWM = 0;                      // 右モータの出力

    // 目標距離を走り終えるまでループ
    while (currentDistance - initialDistance < settings.targetDistance)
    {
        // 旋回値の計算
        turnValue = turnControl.calculateTurn(
            controller.getBrightness(), targetBrightness,
            settings.turnPid.kp, settings.turnPid.ki, settings.turnPid.kd);

        // 前進値の計算
        speedValue = 30;
        /* NOTE: 後日実装予定
        speedValue = speedControl.calculateSpeed(
            settings.speedPid.kp, settings.speedPid.ki, settings.speedPid.kd,
            settings.targetSpeed);
        */

        // モータ出力の計算
        if (isLeftCourse)
        {
            // Leftコースの場合
            leftPWM = speedValue - turnValue;
            rightPWM = speedValue + turnValue;
        }
        else
        {
            // Rightコースの場合
            leftPWM = speedValue + turnValue;
            rightPWM = speedValue - turnValue;
        }

        // PWM値の設定
        controller.setLeftMotorPwm(leftPWM);
        controller.setRightMotorPwm(rightPWM);

        // 現在の走行距離の取得
        currentDistance = distance.getDistance(
            controller.getLeftMotorCount(), controller.getRightMotorCount());
    }
}

/** セッター
 *  @bfief カラーセンサーの目標値を再設定する
 *  @param targetBrightness_ [カラーセンサーの目標値]
 */
void LineTracer::setTargetBrightness(int targetBrightness_)
{
    targetBrightness = targetBrightness_;
}
