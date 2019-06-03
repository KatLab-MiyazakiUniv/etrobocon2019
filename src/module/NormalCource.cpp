/**
 *  @file   NormalCource.cpp
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCource.h"

void NormalCource::selectedEdgeLR(Edge& selectedEdge_) {
  if (selectedEdge_ == Edge::LEFT) {
    selectedEdge = false;
  } else {
    selectedEdge = true;
  }
}

void NormalCource::lineTraceForSpecifiedDistance(double specifiedDistance, int target, int pwm) {
  
  /**
   * ここでPID関連（ライントレース）の準備をする
   */

  while (specifiedDistance >= currentMovedDistance) {
    leftWheel = controller.leftWheel - leftWheel;
    rightWheel = controller.rightWheel - rightWheel;
    
    currentMovedDistance += distance.getDistance(leftWheel, rightWheel);
    // 4msecのdelay
    controller.tslpTsk(4);
  }
  leftWheel = 0;
  rightWheel = 0;
}
