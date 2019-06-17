/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji ()
 */

#include "Navigator.h"

/**
 * コンストラクタ
 * @brief Navigatorクラスのコンストラクタ
 * @param &controller_ [Controllerインスタンスの参照]
 */
Navigator::Navigator(Controller& controller_) : distance(), controller(controller_) {}

/**
 * 前進と後進をする
 * @brief specifiedValueの値でbackwardかforwardを呼び出す。
 * @param specifiedValue [移動したい距離(mm)。正なら前進、負なら後進。]
 * @param pwm [モータの強さ]
 * @return なし
 */
void Navigator::move(double specifiedValue, int pwm)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  if(specifiedValue < 0) {
    backward(specifiedValue, goalDistance, -std::abs(pwm));
  } else {
    forward(specifiedValue, goalDistance, std::abs(pwm));
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

/**
 * @TODO move関数に統合する？ また、IおよびDゲインも指定できるようにする？
 * @brief PID制御を用いて両輪の回転量が等しくなるように前進または後進する
 * @param specifiedValue [移動したい距離(mm)。正なら前進、負なら後進]
 * @param pwm [モータの強さ]
 * @param pGain [Pゲイン]
 * @return なし
 */
void Navigator::moveByPid(double specifiedValue, int pwm, const double pGain, const double iGain,
                          const double dGain)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  // 右車輪の回転量 - 左車輪の回転量
  // 右車輪の方が多く回転していれば、alphaは正となり左車輪にPWM + alphaの操作量が加えられる
  Pid pid(pGain, iGain, dGain);
  double alpha = pid.control(rightAngle - leftAngle);

  if(specifiedValue < 0) {
    backward(specifiedValue, goalDistance, pwm, alpha);
  } else {
    forward(specifiedValue, goalDistance, pwm, alpha);
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

/**
 * 前進する
 * @brief モータを動かし、hasArrivedメソッドの戻り値がtrueの間前進する
 * @note デフォルトでは両輪のPWM値に差はない。左右車輪で異なるPWM値をかけるときはalphaを指定する
 * @param specifiedValue [移動したい距離(mm)]
 * @param goalDistance[現在地から移動したい距離動いた後の値(mm)]
 * @param pwm[モータの強さ]
 * @param alpha [左右のPWM値の差]
 * @return なし
 */
void Navigator::forward(double specifiedValue, double goalDistance, int pwm, double alpha)
{
  while(hasArrived(goalDistance, true)) {
    controller.setRightMotorPwm(pwm + alpha);
    controller.setLeftMotorPwm(pwm - alpha);
    controller.tslpTsk(4);
  }
}

/**
 * 後進する
 * @brief モータを動かし、hasArrivedメソッドの戻り値がtrueの間後進する
 * @note デフォルトでは両輪のPWM値に差はない。左右車輪で異なるPWM値をかけるときはalphaを指定する
 * @param specifiedValue [移動したい距離(mm)]
 * @param goalDistance[現在地から移動したい距離動いた後の値(mm)]
 * @param pwm[モータの強さ]
 * @param alpha [左右のPWM値の差]
 * @return なし
 */
void Navigator::backward(double specifiedValue, double goalDistance, int pwm, double alpha)
{
  while(hasArrived(goalDistance, false)) {
    controller.setRightMotorPwm(pwm + alpha);
    controller.setLeftMotorPwm(pwm - alpha);
    controller.tslpTsk(4);
  }
}

/**
 * 指定した距離動いたか判定する
 * @brief 現在値とgoalDistanceを比較し、resultに"true"か"false"を格納する
 * @param goalDistance [現在地から移動したい距離動いた後の値(mm)]
 * @param isForward [前進なら"true"、後進なら"false"]
 * @return result [移動したい距離動いたら"true"、動いていないなら"false"]
 */
bool Navigator::hasArrived(double goalDistance, bool isForward)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();

  // スタート地点からみた現在の距離
  int currentDistance = distance.getDistance(leftAngle, rightAngle);

  if(isForward) {
    return currentDistance <= goalDistance;
  } else {
    return currentDistance >= goalDistance;
  }
}
