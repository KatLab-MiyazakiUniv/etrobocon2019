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

/*
NOTE
    Distance は保留
    PID値の設定と取得をできるようにする
    目標走行距離とPIDの値を取得し、指定距離走行したら処理を戻す(return)
    目標の明るさはコンストラクタで渡す。
    目標の明るさのセッターを作成
    左エッジか右エッジかはboolでコンストラクタに渡す
*/

struct PidNum
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
    PidNum speedPid;
    // turnPid
    PidNum turnPid;
};

class LineTracer
{
public:
    /** コンストラクタ
     *  @param target  [カラーセンサーの目標値]
     *  @param isRight [Rightコースであるか否か]
     */
    LineTracer(int target, bool isRight);

    /** 指定された距離だけ走行する。
     *  @bfief
     *  走行距離や目標スピード、スピード制御PID、回転制御PIDを NormalCourceProperty 構造体を使用し、渡す。
     *  @param settings [各種が入っている NormalCourceProperty 構造体]
     */
    void run(NormalCourceProperty &settings);

    // カラーセンサー目標値のセッター
    void setTargetBrightness(int targetBrightness);

private:
    int targetBrightness;
    bool isRightCourse;
    Distance distance;
    SpeedControl speedControl;
    TurnControl turnControl;
    Controller controller;
};

#endif
