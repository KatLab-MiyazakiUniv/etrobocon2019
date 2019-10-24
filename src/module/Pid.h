/**
 *  @file   Pid.h
 *  @brief  PID制御クラス
 *  @author T.Miyaji
 */
#ifndef PID_H
#define PID_H

// constexprなPID制御のみで用いる定数をまとめた構造体
struct ConstPidGain {
  double Kp;  // Pゲイン
  double Ki;  // Iゲイン
  double Kd;  // Dゲイン
  constexpr ConstPidGain(double Kp_, double Ki_, double Kd_): Kp(Kp_), Ki(Ki_), Kd(Kd_){}
};

// PID制御のみで用いる定数をまとめた構造体
struct PidGain: public ConstPidGain {
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
  Pid(double target_, double Kp_, double Ki_ = 0.0, double Kd_ = 0.0);
  double control(double value, double delta = 0.004);
  const double setParameter(double target_, double Kp_, double Ki_ = 0.0, double Kd_ = 0.0);
  const PidGain& setPidGain(double Kp_, double Ki_ = 0.0, double Kd_ = 0.0);
  double limit(double value);
};

#endif
