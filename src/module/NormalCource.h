/**
 *  @file   NormalCource.h
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURCE_H
#define NORMALCOURCE_H
#include "Distance.h"
#include "Controller.h"

// #include "Controller.h"

enum struct Edge {LEFT, RIGHT};

class NormalCource
{
private:
  //! 現在進んだ距離．単位はmm
  double currentMovedDistance;
  //! エッジがどっちか． falseが左エッジ，trueが右エッジ
  bool selectedEdge;
  //! 左のモータ角度
  int leftWheel;
  //! 右のモータ角度
  int rightWheel;
  //! 距離を測るインスタンス
  Distance distance;
  //! コントローラーインスタンス
  Controller controller;
public:
  //! コンストラクタ
  NormalCource(Edge& selectedEdge_) : currentMovedDistance(0.0f), leftWheel(0), rightWheel(0)
  {
    NormalCource::selectedEdgeLR(selectedEdge_);
  }

/**
 * 左エッジ，右エッジを切り替える．
 * @param Edge::LEFT or, Edge::RIGHT
 */
void selectedEdgeLR(Edge& selectedEdge_);

/**
 * 引数として受け取った距離だけライントレースする．
 * @param specifiedDistance 進みたい距離．単位はmm
 * @param target 黒色と白色の境界の輝度値
 * @param pwm モータパワー
 */
void  lineTraceForSpecifiedDistance(double specifiedDistance, int target, int pwm);
};

#endif
