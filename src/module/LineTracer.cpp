/**
 *  @file   LineTracer.cpp
 *  @brief  ライントレースを行うクラス
 *  @author Takahiro55555
 */

#include "LineTracer.h"

/** コンストラクタ
 *  @param target  [カラーセンサーの目標値]
 *  @param isRight [Rightコースであるか否か]
 */
LineTracer::LineTracer(int target, bool isRight)
    : targetBrightness(target), isRightCourse(isRight) {}

/** 指定された距離だけ走行する。
 *  @bfief
 *  走行距離や目標スピード、スピード制御PID、回転制御PIDを NormalCourceProperty 構造体を使用し渡す。
 *  @param settings [各種が入っている NormalCourceProperty 構造体]
 */
void LineTracer::run(NormalCourceProperty &settings)
{
    // 関数呼び出し時の走行距離を取得・設定
    int initialDistance = distance.getDistance(
        controller.leftWheel.getCount(), controller.rightWheel.getCount());

    int currentDistance = initialDistance; // 現在の走行距離
    int turnValue;                         // 旋回値
    int speedValue;                        // 直進値
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
        speedValue = speedControl.calculateSpeed(
            settings.speedPid.kp, settings.speedPid.ki, settings.speedPid.kd,
            settings.targetSpeed);

        // モータ出力の計算
        if (isRightCourse)
        {
            // Rightコースの場合
            leftPWM = speedValue + turnValue;
            rightPWM = speedValue - turnValue;
        }
        else
        {
            // Leftコースの場合
            leftPWM = speedValue - turnValue;
            rightPWM = speedValue + turnValue;
        }

        // PWM値の設定
        controller.leftWheel.setPWM(leftPWM);
        controller.rightWheel.setPWM(rightPWM);

        // 現在の走行距離の取得
        currentDistance = distance.getDistance(
            controller.leftWheel.getCount(), controller.rightWheel.getCount());
    }
}

// カラーセンサー目標値のセッター
void LineTracer::setTargetBrightness(int brightness)
{
    targetBrightness = brightness;
}