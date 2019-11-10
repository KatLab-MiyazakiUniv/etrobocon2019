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

 private:
  Controller& controller;
  int targetBrightness;
  bool isLeftCourse;
  Distance distance;
  TurnControl turnControl;
};

#endif
