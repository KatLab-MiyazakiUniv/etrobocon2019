/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURSE_H
#define NORMALCOURSE_H
#include <array>
#include "LineTracer.h"
#include "Controller.h"

class NormalCourse {
 public:
  /** コンストラクタ
   *  @param controller [コントローラのインスタンス]
   *  @param targetBrightness_ [カラーセンサーの目標値]
   */
  NormalCourse(Controller& controller_, int targetBrightness_);

  /**
   * 左エッジ，右エッジを切り替える．
   * @param selectedEdge_ [Leftコースである場合True]
   */
  void selectedEdgeLR(bool selectedEdge_);

  /**
   * 実際にNormalコースを走る．
   */
  void runNormalCourse();

  /**
   * 現在のselectedEdge（エッジ）を返すゲッター
   */
  bool getSelectedEdge();

  /**
   * targetBrightness（カラーセンサの目標値）を返すゲッター
   */
  int getTargetBrightness();

 private:
  //! コントローラー
  Controller& controller;
  //! エッジがどっちか． trueが左コース，falseが右コース
  bool selectedEdge;
  //! カラーセンサーの目標値
  int targetBrightness;
};

#endif
