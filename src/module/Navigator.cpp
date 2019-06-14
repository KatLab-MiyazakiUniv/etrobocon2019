/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 */

#include "Navigator.h"

/**
 * コンストラクタ
 * @brief Navigatorクラスのコンストラクタ
 * @param &controller_ [Controllerインスタンスの参照]
 */
Navigator::Navigator(Controller& controller_)
 : distance(), controller(controller_) {}

/**
 * 前進と後進をする
 * @brief specifiedValueの値でbackwardかforwardを呼び出す。
 * @param specifiedValue [移動したい距離(mm)。正なら前進、負なら後進。]
 * @param pwm [モータの強さ]
 * @return なし
 */
void Navigator::move(int specifiedValue, int pwm)
{
  int leftAngle = controller.leftWheel.getCount();
  int rightAngle = controller.rightWheel.getCount();
  int goalDistance = specifiedValue + static_cast<int>(distance.getDistance(leftAngle, rightAngle));

  if(specifiedValue < 0)
  {
    backward(specifiedValue, -std::abs(pwm), goalDistance);
  }
  else
  {
    forward(specifiedValue, std::abs(pwm), goalDistance);
  }

  controller.rightWheel.setPWM(0);
  controller.leftWheel.setPWM(0);
}

/**
 * 前進する
 * @brief モータを動かし、hasArrivedメソッドの戻り値がtrueの間前進する
 * @param specifiedValue [移動したい距離(mm)]
 * @param pwm[モータの強さ]
 * @param goalDistance[現在地から移動したい距離動いた後の値(mm)]
 * @return なし
 */
void Navigator::forward(int specifiedValue, int pwm, int goalDistance)
{
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);

  while(hasArrived(goalDistance, true)) {
    controller.tslpTsk(4);
  }
}

/**
 * 後進する
 * @brief hasArrivedメソッドの戻り値がtrueの間後進する
 * @param specifiedValue [移動したい距離(mm)]
 * @param pwm[モータの強さ]
 * @param goalDistance[現在地から移動したい距離動いた後の値(mm)]
 * @return なし
 */
void Navigator::backward(int specifiedValue, int pwm, int goalDistance)
{
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);

  while(hasArrived(goalDistance, false)) {
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
bool Navigator::hasArrived(int goalDistance, bool isForward)
{
  int leftAngle = controller.leftWheel.getCount();
  int rightAngle = controller.rightWheel.getCount();

  bool result = true;
  if(isForward)
  {
    result = (distance.getDistance(leftAngle, rightAngle) <= goalDistance);
  }
  else
  {
    result = (distance.getDistance(leftAngle, rightAngle) >= goalDistance);
  }

  return result;
}