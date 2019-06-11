/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURSE_H
#define NORMALCOURSE_H

#include "LineTracer.h"  // 仮のヘッダファイル
#include <array>

class NormalCourse {
 private:
  //! 配列の要素数（コンパイル時に解決）
  template <std::size_t SIZE>
  //! エッジがどっちか． trueが左エッジ，falseが右エッジ
  bool selectedEdge;
  //! 明るさ
  int targetBrightness;

 public:
  //! コンストラクタ
  NormalCourse(bool selectedEdge_, int targetBrightness_)
    : targetBrightness(targetBrightness_), selectedEdge(false)
  {
  }

  /**
   * 左エッジ，右エッジを切り替える．
   * @param Edge::LEFT or, Edge::RIGHT
   */
  void selectedEdgeLR(bool selectedEdge_);

  /**
   * 引数として受け取った距離だけライントレースする．（配列バージョン）
   * @param normalCourseProperty NormalCourseProperty構造体の配列
   */
  void lineTraceForSpecifiedDistance(std::array<NormalCourseProperty, SIZE>& normalCourseProperty);

  /**
   * 引数として受け取った距離だけライントレースする．（配列じゃないバージョン）
   * @param normalCourseProperty NormalCourseProperty構造体
   */
  void lineTraceForSpecifiedDistance(NormalCourseProperty& normalCourseProperty);

  /**
   * 実際にNormalコースを走る．
   */
  void runNormalCourse();
};

#endif
