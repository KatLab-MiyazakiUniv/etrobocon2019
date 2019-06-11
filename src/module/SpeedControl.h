/**
 *  @file  SpeedControl.h
 *  @brief  前進値制御クラス
 *  @author M.Matsuura
 */
#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include "Distance.h"
#include "Pid.h"
#include <cmath>

class SpeedControl
{
private:
    Controller controller;
    Distance dist;
    const double C;   //定数C(実験で求める予定)
    const int radius; //タイヤの半径[mm]
    double prevDistance;

public:
    SpeedControl();
    double calculateSpeed(int targetSpeed, double Kp, double Ki, double Kd);
};

#endif