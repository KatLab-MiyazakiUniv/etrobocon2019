/**
 *  @file   LineTracer.cpp
 *  @brief  ライントレースを行うクラス
 *  @author Takahiro55555
 */
#ifndef LINE_TRACER_H
#define LINE_TRACER_H

#include "Controller.h"
#include "Distance.h"
#include "SpeedControl.h"
#include "TurnControl.h"


struct PidParameter
{
    // p値
    double kp;
    // k値
    double ki;
    // d値
    double kd;
};

struct NormalCourceProperty
{
    // 目標距離
    int targetDistance;
    // 目標スピード
    int targetSpeed;
    // speedPid
    PidParameter speedPid;
    // turnPid
    PidParameter turnPid;
};

class LineTracer
{
public:
    /** コンストラクタ
     *  @param targetBrightness_  [カラーセンサーの目標値]
     *  @param isRightCourse_ [Rightコースである場合True]
     */
    LineTracer(int targetBrightness_, bool isRightCourse_);

    /** 指定された距離だけ走行する。
     *  @bfief 走行距離や目標スピード、スピード制御PID、回転制御PIDを NormalCourceProperty 構造体を使用し渡す。
     *  @param settings [各種パラメータが入っている NormalCourceProperty 構造体]
     */
    void run(NormalCourceProperty &settings);

    /** セッター
     *  @bfief カラーセンサーの目標値を再設定する
     *  @param targetBrightness_ [カラーセンサーの目標値]
     */
    void setTargetBrightness(int targetBrightness_);

private:
    int targetBrightness;
    bool isRightCourse;
    Distance distance;
    SpeedControl speedControl;
    TurnControl turnControl;
    Controller controller;
};

#endif
