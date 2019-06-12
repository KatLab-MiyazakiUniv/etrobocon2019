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
Navigator::Navigator(Controller &controller_)
    : distance(), controller(controller_)
{
}

/**
 * 前進と後進をする
 * @brief specifiedValueの値でbackwardかforwardを呼び出す。
 * @param specifiedValue [移動したい距離(mm)。正なら前進、負なら後進。]
 * @param pwm [モーターの強さ]
 * @return なし
 */
void Navigator::move(int specifiedValue, int pwm)
{
  int leftAngle = controller.leftWheel.getCount();
  int rightAngle = controller.rightWheel.getCount();
  int goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  if (specifiedValue < 0)
  {
    backward(specifiedValue, -std::abs(pwm), goalDistance);
  }
  else{
    forward(specifiedValue, std::abs(pwm), goalDistance);
  }

  controller.rightWheel.setPWM(0);
  controller.leftWheel.setPWM(0);
}

/**
 * @brief
 * @param
 * @return
 */
void Navigator::forward(int specifiedValue, int pwm, int goalDistance) 
{
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);

  while (isMoved(goalDistance,true))
  {
    controller.tslpTsk(4);
  }
}

/**
 * @brief
 * @param
 * @return
 */
void Navigator::backward(int specifiedValue, int pwm, int goalDistance)
{
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);

  while (isMoved(goalDistance,false))
  {
    controller.tslpTsk(4);
  }
}

bool Navigator::isMoved(int goalDistance, bool isForward)
{
  int leftAngle = controller.leftWheel.getCount();
  int rightAngle = controller.rightWheel.getCount();

  bool result;
  if(isForward)
  {
    result = distance.getDistance(leftAngle, rightAngle) <= goalDistance
  }
  else
  {
    result = distance.getDistance(leftAngle, rightAngle) >= goalDistance
  }

  return result;
}