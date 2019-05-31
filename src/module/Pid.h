/**
 *  @file   Pid.h
 *  @brief  PID制御クラス
 *  @author T.Miyaji
 */
#ifndef PID_H
#define PID_H

// PID制御のみで用いる定数をまとめた構造体
struct PidGain {
  float Kp_;  // Pゲイン
  float Ki_;  // Iゲイン
  float Kd_;  // Dゲイン
  PidGain(float Kp, float Ki, float Kd);
  void setPidGain(float Kp, float Ki, float Kd);
};

class Pid {
 private:
  float target_;
  PidGain gain_;
  float preError_;
  float integral_;

 public:
  Pid(float target, float Kp, float Ki = 0.0f, float Kd = 0.0f);
};

#endif
