/**
 *  @file   LineTracer.cpp
 *  @brief  ライントレースを行うクラス
 *  @author Takahiro55555
 */
#ifndef LINE_TRACER_H
#define LINE_TRACER_H

#include "Controller.h"
#include "Distance.h"
#include "TurnControl.h"
#include "Pid.h"
#include "Curvature.h"

struct NormalCourseProperty {
  // 目標距離
  int targetDistance;
  // 目標スピード
  int targetSpeed;
  // 曲率
  double curvature;
  // turnPid
  ConstPidGain turnPid;
};

class LineTracer {
 public:
  /** コンストラクタ
   *  @param controller_  [Controller]
   *  @param targetBrightness_  [カラーセンサーの目標値]
   *  @param isLeftCourse_ [Leftコースである場合True]
   */
  LineTracer(Controller& controller_, int targetBrightness_, bool isLeftCourse_);

  /** 指定された距離だけ走行する。
   *  @brief 走行距離や目標スピード、スピード制御PID、回転制御PIDを NormalCourseProperty
   * 構造体を使用し渡す。
   *  @param settings [各種パラメータが入っている NormalCourseProperty 構造体]
   */
  void run(const NormalCourseProperty& settings);

  /** セッター
   *  @brief カラーセンサーの目標値を再設定する
   *  @param targetBrightness_ [カラーセンサーの目標値]
   */
  void setTargetBrightness(int targetBrightness_);

  /** 旋回値を計算する。
   *  @brief カラーセンサーの値を用いたPID制御と曲率PID制御を組み合わせて計算した旋回値を返す
   *  @param speedValue [前進値]
   *  @param curvatureValue [曲率(直進時は、0.0)]
   *  @param pGain [カラーセンサーの値を用いたPID制御のPゲイン]
   *  @param iGain [カラーセンサーの値を用いたPID制御のIゲイン]
   *  @param dGain [カラーセンサーの値を用いたPID制御のDゲイン]
   */
  int calculateTurnValue(int speedValue, double curvatureValue, double pGain, double iGain,
                         double dGain);

 private:
  Controller& controller;
  int targetBrightness;
  bool isLeftCourse;
  Distance distance;
  TurnControl turnControl;
};

#endif
