/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi0000
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
   *  @param isLeftCourse_ [エッジがどっちかtrueがLeftコース]
   *  @param targetBrightness_ [カラーセンサーの目標値]
   */
  NormalCourse(Controller& controller_, bool isLeftCourse_, int targetBrightness_);

  /**
   * 左エッジ，右エッジを切り替える．
   * @param isLeftCourse_ [Leftコースである場合True]
   */
  void setIsLeftCourse(bool isLeftCourse_);

  /**
   * 実際にNormalコースを走る．
   */
  void runNormalCourse();

  /**
   * 現在のisLeftCourse（エッジ）を返すゲッター
   */
  bool getIsLeftCourse() const;

  /**
   * targetBrightness（カラーセンサの目標値）を返すゲッター
   */
  int getTargetBrightness() const;

 private:
  //! コントローラー
  Controller& controller;
  //! エッジがどっちか． trueが左コース，falseが右コース
  bool isLeftCourse;
  //! カラーセンサーの目標値
  int targetBrightness;
};

#endif
