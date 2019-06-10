/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURSE_H
#define NORMALCOURSE_H

#include "LineTracer.h" // 仮のヘッダファイル
#include <array>

// #include "Controller.h"
enum struct Edge
{
  LEFT,
  RIGHT
};

class NormalCourse
{
private:
  //! エッジがどっちか． falseが左エッジ，trueが右エッジ
  bool selectedEdge;
  //! ライントレースのインスタンス
  LineTracer lineTrace;
  //! 明るさ
  int targetBrightness;

  template <size_t N>

  public :
      //! コンストラクタ
      NormalCourse(Edge &selectedEdge_, int targetBrightness_)
      : targetBrightness(targetBrightness_)
  {
    NormalCourse::selectedEdgeLR(selectedEdge_);
    lineTrace(selectedEdge, targetBrightness);
  }

  /**
   * 左エッジ，右エッジを切り替える．
   * @param Edge::LEFT or, Edge::RIGHT
   */
  void selectedEdgeLR(Edge &selectedEdge_);

  /**
   * 引数として受け取った距離だけライントレースする．
   * @param specifiedDistance 進みたい距離．単位はmm
   * @param target 黒色と白色の境界の輝度値
   * @param pwm モータパワー
   */
  void lineTraceForSpecifiedDistance(std::array<NormalCourseProperty, N> NormalCourseProperty);
};

#endif
