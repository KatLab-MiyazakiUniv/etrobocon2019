/**
 *  @file  SpeedControl.h
 *  @brief  前進値制御クラス
 *  @author M.Matsuura
 */
#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include "Distance.h"
#include "Pid.h"

class SpeedControl
{
private:
 double delta;
 double currentSpeed;
public:
    SpeedControl();
    int calculateSpeed(int targetSpeed,double Kp,double Ki,double Kd);
};

#endif