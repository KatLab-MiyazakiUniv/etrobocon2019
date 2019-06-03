/**
 *  @file   Pid.h
 *  @brief  PID制御クラス
 *  @author T.Miyaji
 */
#ifndef PID_H
#define PID_H

// PID制御のみで用いる定数をまとめた構造体
struct PidGain {
  double Kp;  // Pゲイン
  double Ki;  // Iゲイン
  double Kd;  // Dゲイン
  PidGain(double Kp_, double Ki_, double Kd_);
  void setPidGain(double Kp_, double Ki_, double Kd_);
};

class Pid {
 private:
  double target;
  PidGain gain;
  double integral;
  double preError;

 public:
  Pid(double target_, double Kp_, double Ki_ = 0.0f, double Kd_ = 0.0f);
  double control(double value, double delta = 0.004);
  double limit(double value);
};

#endif
