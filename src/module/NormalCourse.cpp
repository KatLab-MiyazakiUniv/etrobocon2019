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
NormalCourse::NormalCourse(Controller& controller_, int targetBrightness_)
  : controller(controller_), selectedEdge(false), targetBrightness(targetBrightness_)
{
}

/**
 * 左エッジ，右エッジを切り替える．
 * @param selectedEdge_ [Leftコースである場合True]
 */
void NormalCourse::selectedEdgeLR(bool selectedEdge_)
{
  selectedEdge = selectedEdge_;
  NormalCourse::runNormalCourse();
}

/**
 * 実際にNormalコースを走る．
 * ここにパラメータを頑張って書く．
 */
void NormalCourse::runNormalCourse()
{
  // 配列の個数
  constexpr int arraySize = 2;
  std::array<PidParameter, arraySize> speedPid = { { { 0.1, 0.0, 0.0 }, { 0.1, 0.01, 0.0 } } };
  std::array<PidParameter, arraySize> turnPid = { { { 0.1, 0.0, 0.0 }, { 0.1, 0.01, 0.0 } } };
  std::array<NormalCourseProperty, arraySize> normalCourseProperty
      = { { { 1000, 10, speedPid[0], turnPid[0] }, { 500, 80, speedPid[1], turnPid[1] } } };

  LineTracer lineTracer(targetBrightness, selectedEdge);
  for(auto& ncp : normalCourseProperty) {
    lineTracer.run(ncp);
    // １区間終わるごとに音を奏でる．
    controller.speakerPlayToneFS6(100);
  }
}

/**
 * 現在のselectedEdge（エッジ）を返すゲッター
 */
bool NormalCourse::getSelectedEdge()
{
  return selectedEdge;
}

/**
 * targetBrightness（カラーセンサの目標値）を返すゲッター
 */
int NormalCourse::getTargetBrightness()
{
  return targetBrightness;
}
