/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCourse.h"

/** コンストラクタ
 *  @param controller [コントローラのインスタンス]
 *  @param targetBrightness_ [カラーセンサーの目標値]
 */
NormalCourse::NormalCourse(Controller& controller_, bool isLeftCourse_, int targetBrightness_)
  : controller(controller_), isLeftCourse(isLeftCourse_), targetBrightness(targetBrightness_)
{
}

/**
 * 左エッジ，右エッジを切り替える．
 * @param selectedEdge_ [Leftコースである場合True]
 */
void NormalCourse::setIsLeftCourse(bool isLeftCourse_)
{
  isLeftCourse = isLeftCourse_;
}

/**
 * 実際にNormalコースを走る．
 * ここにパラメータを頑張って書く．
 */
void NormalCourse::runNormalCourse()
{
  // 配列の個数
  constexpr int arraySize = 2;
  std::array<NormalCourseProperty, arraySize> normalCourseProperty
      = { { { 1000, 10, { 0.1, 0.0, 0.0 }, { 0.1, 0.01, 0.0 } },     // 第1区間
            { 500, 80, { 0.1, 0.0, 0.0 }, { 0.1, 0.01, 0.0 } } } };  // 第2区間

  LineTracer lineTracer(targetBrightness, isLeftCourse);
  for(auto& ncp : normalCourseProperty) {
    lineTracer.run(ncp);
    // １区間終わるごとに音を奏でる．
    controller.speakerPlayToneFS6(100);
  }
}

/**
 * 現在のselectedEdge（エッジ）を返すゲッター
 */
bool NormalCourse::getIsLeftCourse()
{
  return isLeftCourse;
}

/**
 * targetBrightness（カラーセンサの目標値）を返すゲッター
 */
int NormalCourse::getTargetBrightness()
{
  return targetBrightness;
}
