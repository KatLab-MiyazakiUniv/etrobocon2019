/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURSE_H
#define NORMALCOURSE_H
#include <array>
#include "LineTracer.h"

class NormalCourse {
 public:
  /** コンストラクタ
   *  @param selectedEdge_  [Leftコースである場合True]
   *  @param targetBrightness_ [カラーセンサーの目標値]
   */
  NormalCourse(bool selectedEdge_, int targetBrightness_);

  /**
   * 左エッジ，右エッジを切り替える．
   * @param selectedEdge_ [Leftコースである場合True]
   */
  void selectedEdgeLR(bool selectedEdge_);

  /**
   * 引数として受け取った距離だけライントレースする．（配列バージョン）
   * @param normalCourseProperty NormalCourseProperty構造体の配列
   */
  template <typename std::size_t N>
  void lineTraceForSpecifiedDistance(std::array<NormalCourseProperty, N>& ncpArray);

  /**
   * 引数として受け取った距離だけライントレースする．（配列じゃないバージョン）
   * @param normalCourseProperty NormalCourseProperty構造体
   */
  // void lineTraceForSpecifiedDistance(NormalCourseProperty& normalCourseProperty);

  /**
   * 実際にNormalコースを走る．
   */
  void runNormalCourse();

 private:
  //! エッジがどっちか． trueが左コース，falseが右コース
  bool selectedEdge;
  //! 目標の輝度値
  int targetBrightness;
  //!
  LineTracer lineTracer;
};

#endif
