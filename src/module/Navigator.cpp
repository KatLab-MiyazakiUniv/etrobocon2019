/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#include "Navigator.h"

<<<<<<< HEAD
Navigator::Navigator(Controller& controller_, int targetBrightness_, double Kp_, double Ki_,
                     double Kd_)
  : distance(),
    controller(controller_),
    pidForSpeed(Kp_, Ki_, Kd_),
    targetBrightness(targetBrightness_)
{
}

void Navigator::setPidGain(double Kp, double Ki, double Kd)
{
  pidForSpeed.setPidGain(Kp, Ki, Kd);
}

=======
Navigator::Navigator(Controller& controller_, int targetBrightness_)
  : distance(), controller(controller_), targetBrightness(targetBrightness_)
{
}

>>>>>>> upstream/master
void Navigator::move(double specifiedDistance, int pwm, const double pGain)
{
  controller.resetMotorCount();

  // 左車輪の回転量 - 右車輪の回転量
  // 左車輪の方が多く回転していれば、alphaは正となり右車輪にPWM + alphaの操作量が加えられる
  Pid pid(0, pGain);

  if(specifiedDistance < 0) {
    while(hasArrived(specifiedDistance, false)) {
      double alpha = pid.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      setPwmValue(-std::abs(pwm), -alpha);
      controller.tslpTsk(4);
    }
  } else {
    while(hasArrived(specifiedDistance, true)) {
      double alpha = pid.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      setPwmValue(std::abs(pwm), -alpha);
      controller.tslpTsk(4);
    }
  }

  controller.stopMotor();
}

<<<<<<< HEAD
void Navigator::moveAtSpecifiedSpeed(double specifiedDistance, int specifiedSpeed)
{
  controller.resetMotorCount();

  SpeedControl speedControl(controller, specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                            pidForSpeed.Kd);

  if(specifiedDistance < 0) {
    while(hasArrived(specifiedDistance, false)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                                               pidForSpeed.Kd);
      setPwmValue(static_cast<int>(-std::abs(pwm)));
      controller.tslpTsk(4);
    }
  } else {
    while(hasArrived(specifiedDistance, true)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                                               pidForSpeed.Kd);
      setPwmValue(static_cast<int>(std::abs(pwm)));
      controller.tslpTsk(4);
    }
  }
  controller.stopMotor();
}

void Navigator::moveToSpecifiedColor(Color specifiedColor, int pwm)
{
  if(specifiedColor == Color::black || specifiedColor == Color::white) {
    while(specifiedColor != recognizeBlack(controller.getBrightness())) {
      setPwmValue(pwm);
      controller.tslpTsk(4);
    }
  } else {
    // 特定の色まで移動する
    while(controller.determineColor() != specifiedColor) {
      setPwmValue(pwm);
      controller.tslpTsk(4);
    }
=======
void Navigator::moveToSpecifiedColor(Color specifiedColor, int pwm)
{
  // 特定の色まで移動する
  while(controller.getColor() != specifiedColor) {
    setPwmValue(pwm);
    controller.tslpTsk(4);
>>>>>>> upstream/master
  }
  controller.stopMotor();
}

<<<<<<< HEAD
void Navigator::spin(double angle, bool clockwise, int pwm)
=======
void Navigator::spin(double angle, bool clockwise, int pwm, double weight)
>>>>>>> upstream/master
{
  // angleの絶対値を取る
  angle = std::abs(angle);
  Rotation rotation;
<<<<<<< HEAD

  controller.resetMotorCount();

  while(rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount())
        < angle) {
    controller.setLeftMotorPwm(clockwise ? pwm : -pwm);
    controller.setRightMotorPwm(clockwise ? -pwm : pwm);
    controller.tslpTsk(4);
=======
  Filter<> filter;

  controller.resetMotorCount();
  controller.resetGyroSensor();

  double motorAngle
      = rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());
  double gyroAngle = std::abs(static_cast<double>(controller.getAngleOfRotation()));

  while(filter.complementaryFilter(motorAngle, gyroAngle) < angle) {
    controller.setLeftMotorPwm(clockwise ? pwm : -pwm);
    controller.setRightMotorPwm(clockwise ? -pwm : pwm);
    controller.tslpTsk(4);

    motorAngle
        = rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());
    gyroAngle = std::abs(static_cast<double>(controller.getAngleOfRotation()));
>>>>>>> upstream/master
  }

  controller.stopMotor();
}

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

void Navigator::setPwmValue(int pwm, double alpha)
{
  controller.setRightMotorPwm(pwm + static_cast<int>(alpha));
  controller.setLeftMotorPwm(pwm - static_cast<int>(alpha));
}

<<<<<<< HEAD
Color Navigator::recognizeBlack(int brightness)
{
  return brightness < targetBrightness ? Color::black : Color::white;
}

void Navigator::traceBlackLineToSpecifiedColor(Color specifiedColor, int pwm, double pGain,
                                               bool isLeft)
{
  Pid pid(targetBrightness, pGain);

  // 特定の色まで移動する
  while(controller.determineColor() != specifiedColor) {
    double pidValue = pid.control(controller.getBrightness());
    this->setPwmValue(pwm, (isLeft ? pidValue : -pidValue));
    controller.tslpTsk(4);
  }
=======
void Navigator::lineTrace(double specifiedDistance, int pwm, double encoderPGain,
                          double lineTracePGain, bool isLeft)
{
  controller.resetMotorCount();

  // 左車輪の回転量 - 右車輪の回転量
  // 左車輪の方が多く回転していれば、alphaは正となり右車輪にPWM + alphaの操作量が加えられる
  Pid pidForEncoder(0, lineTracePGain);

  Pid pidForLineTrace(targetBrightness, lineTracePGain);

  if(specifiedDistance < 0) {
    // 指定した距離に到達するまでTrue
    while(hasArrived(specifiedDistance, false)) {
      // エンコーダーの値をp制御
      double encoderPidValue
          = pidForEncoder.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      // ライントレース用のp制御
      double lineTracePidValue = pidForLineTrace.control(controller.getBrightness());

      // 後進するため、pwmは負の値
      int rightPwm = -std::abs(pwm)
                     + static_cast<int>(isLeft ? lineTracePidValue : -lineTracePidValue)
                     - static_cast<int>(encoderPidValue);
      int leftPwm = -std::abs(pwm)
                    + static_cast<int>(isLeft ? -lineTracePidValue : lineTracePidValue)
                    + static_cast<int>(encoderPidValue);

      controller.setRightMotorPwm(rightPwm);
      controller.setLeftMotorPwm(leftPwm);

      controller.tslpTsk(4);
    }
  } else {
    // 上記のwhile文の中の処理とほぼ同じ
    while(hasArrived(specifiedDistance, true)) {
      double encoderPidValue
          = pidForEncoder.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      double lineTracePidValue = pidForLineTrace.control(controller.getBrightness());

      // 前進するため、pwmは正の値
      int rightPwm = std::abs(pwm)
                     + static_cast<int>(isLeft ? lineTracePidValue : -lineTracePidValue)
                     - static_cast<int>(encoderPidValue);
      int leftPwm = std::abs(pwm)
                    + static_cast<int>(isLeft ? -lineTracePidValue : lineTracePidValue)
                    + static_cast<int>(encoderPidValue);

      controller.setRightMotorPwm(rightPwm);
      controller.setLeftMotorPwm(leftPwm);

      controller.tslpTsk(4);
    }
  }

  controller.stopMotor();
}

void Navigator::lineTraceToSpecifiedColor(Color specifiedColor, int pwm, double lineTracePGain,
                                          bool isLeft)
{
  constexpr int resolution = 3;
  LineTracer lineTracer(controller, targetBrightness, isLeft);
  // 循環バッファーを作成する(最初は、noneで埋めておく)
  constexpr int bufferSize = 2 * resolution + 1;
  std::array<Color, bufferSize> circulation;
  circulation.fill(Color::none);
  unsigned int index = 0;
  int count = 0;  // 指定色が循環バッファに存在する個数

  while(count < resolution) {
    count = this->countColorInBuffer<bufferSize>(circulation, index, specifiedColor);

    // ライントレースする
    int turnValue = lineTracer.calculateTurnValue(pwm, 0.0, lineTracePGain, 0.0, 0.0);
    setPwmValue(pwm, (isLeft ? turnValue : -turnValue));

    controller.tslpTsk(4);
  }

  controller.stopMotor();
}

void Navigator::lineTraceExcludingMonochrome(int pwm, double lineTracePGain, bool isLeft)
{
  constexpr int resolution = 3;
  LineTracer lineTracer(controller, targetBrightness, isLeft);
  // 循環バッファーを作成する(最初は、noneで埋めておく)
  constexpr int bufferSize = 2 * resolution + 1;
  std::array<Color, bufferSize> circulation;
  circulation.fill(Color::none);
  unsigned int index = 0;
  int count = 0;
  Color preColor = Color::none;

  while(count < resolution) {
    count = 1;

    // 循環バッファーに色情報を格納する
    if(circulation.size() <= index) index = 0;
    circulation[index] = controller.getColor();
    ++index;

    for(const auto& color : circulation) {
      if(color != Color::black && color != Color::white && color != Color::none
         && color == preColor) {
        count++;
      } else {
        preColor = color;
        count = 1;
      }
    }

    // ライントレースする
    int turnValue = lineTracer.calculateTurnValue(pwm, 0.0, lineTracePGain, 0.0, 0.0);
    setPwmValue(pwm, (isLeft ? turnValue : -turnValue));

    controller.tslpTsk(4);
  }

>>>>>>> upstream/master
  controller.stopMotor();
}