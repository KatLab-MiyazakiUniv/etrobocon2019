/**
 *  @file  SpeedControl.cpp
 *  @brief  前進値制御クラス
 *  @author M.Matsuura
 */

#include "SpeedControl.h"

SpeedControl::SpeedControl()
    : delta(0.004), currentSpeed(0.0)
{
}

/**
 *  [SpeedControl::calculateSpeed]
 *  @param  targetSpeed [目標の速度]  
 *  @param  Kp          [Pゲイン]
 *  @param  Ki          [Iゲイン]
 *  @param  Kd          [Dゲイン]
 *  @return             [現在の速度]
 */

double SpeedControl::calculateSpeed(int targetSpeed, double Kp, double Ki, double Kd)
{
    Pid pid(static_cast<double>(targetSpeed), Kp, Ki, Kd);
    Distance dist;

    Controller controller;

    // 左右のモータの角位置を取得
    int leftAngle = controller.leftWheel.getCount();
    int rightAngle = controller.rightWheel.getCount();

    // 走行距離の取得[mm]
    double distance = dist.getDistance(leftAngle, rightAngle);

    //pid制御後のPWM値
    double pidSpeed = pid.control(currentSpeed);

    //距離/時間で現在の速度を求める
    currentSpeed = distance / delta;

    //setPWMしてモ左右のモータを回す
    controller.leftWheel.setPWM(pidSpeed);
    controller.rightWheel.setPWM(pidSpeed);

    //4ms待つ
    controller.tslpTsk(4);

    //距離を求める
    distance += dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    //走行体の速度を求める
    currentSpeed = currentSpeed + 2 * distance / delta + currentSpeed;

    //現在の速度を返す
    return currentSpeed;
}
