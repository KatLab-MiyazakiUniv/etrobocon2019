/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi0000
 */
#include "NormalCourse.h"

/** コンストラクタ
 *  @param controller [コントローラのインスタンス]
 *  @param isLeftCourse_ [エッジがどっちかtrueがLeftコース]
 *  @param targetBrightness_ [カラーセンサーの目標値]
 */
NormalCourse::NormalCourse(Controller& controller_, bool isLeftCourse_, int targetBrightness_)
  : controller(controller_), isLeftCourse(isLeftCourse_), targetBrightness(targetBrightness_)
{
}

/**
 * 左エッジ，右エッジを切り替える．
 * @param isLeftCourse_ [Leftコースである場合True]
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
  constexpr int arraySize = 15;
  constexpr int baseSpeed = 70;
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyL
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，スピードpid，ターンpid
       */
      = { {
          { 750, baseSpeed, { 0.4, 0.005, 0.02 } },       // 第1区間
          { 305, baseSpeed, { 0.4, 0.0, 0.02 } },         // 第2区間
          { 580, baseSpeed, { 0.4, 0.0, 0.02 } },         // 第3区間
          { 405, baseSpeed - 10, { 0.4, 0.005, 0.03 } },  // 第4区間
          { 354, baseSpeed - 14, { 0.4, 0.005, 0.03 } },  // 第5区間
          { 534, baseSpeed - 10, { 0.4, 0.005, 0.03 } },  // 第6区間
          { 250, baseSpeed, { 0.4, 0.005, 0.025 } },      // 第7区間
          { 353, baseSpeed, { 0.4, 0.005, 0.025 } },      // 第8区間
          { 900, baseSpeed - 11, { 0.4, 0.005, 0.03 } },  // 第9区間
          { 302, baseSpeed - 11, { 0.5, 0.0, 0.03 } },    // 第10区間
          { 170, baseSpeed - 2, { 0.5, 0.0, 0.03 } },     // 第11区間
          { 153, baseSpeed, { 0.5, 0.0, 0.03 } },         // 第12区間
          { 583, baseSpeed, { 0.5, 0.0, 0.03 } },         // 第13区間
          { 2085, baseSpeed / 3, { 0.4, 0.0, 0.04 } },    //進入ライン
          { 233, baseSpeed / 4, { 0.55, 0.0, 0.04 } },    //本番で要調整
      } };
  constexpr std::array<NormalCourseProperty, arraySize> normalCoursePropertyR
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，スピードpid，ターンpid
       */
      = { {
          { 750, baseSpeed, { 0.4, 0.005, 0.02 } },       // 第1区間
          { 305, baseSpeed, { 0.4, 0.0, 0.02 } },         // 第2区間
          { 580, baseSpeed, { 0.4, 0.0, 0.02 } },         // 第3区間
          { 405, baseSpeed - 10, { 0.4, 0.005, 0.03 } },  // 第4区間
          { 354, baseSpeed - 14, { 0.4, 0.005, 0.03 } },  // 第5区間
          { 534, baseSpeed - 10, { 0.4, 0.005, 0.03 } },  // 第6区間
          { 250, baseSpeed, { 0.4, 0.005, 0.025 } },      // 第7区間
          { 353, baseSpeed, { 0.4, 0.005, 0.025 } },      // 第8区間
          { 900, baseSpeed - 11, { 0.4, 0.005, 0.03 } },  // 第9区間
          { 302, baseSpeed - 11, { 0.5, 0.0, 0.03 } },    // 第10区間
          { 170, baseSpeed - 2, { 0.5, 0.0, 0.03 } },     // 第11区間
          { 153, baseSpeed, { 0.5, 0.0, 0.03 } },         // 第12区間
          { 583, baseSpeed, { 0.5, 0.0, 0.03 } },         // 第13区間
          { 2085, baseSpeed / 3, { 0.4, 0.0, 0.04 } },    //進入ライン
          { 233, baseSpeed / 4, { 0.55, 0.0, 0.04 } },    //本番で要調整
      } };
  // LコースならLコースのPID値を採用する。RコースならRコースのPID値を採用する。
  const std::array<NormalCourseProperty, arraySize> normalCourseProperty
      = isLeftCourse ? normalCoursePropertyL : normalCoursePropertyR;
  LineTracer lineTracer(controller, targetBrightness, isLeftCourse);
  for(const auto& ncp : normalCourseProperty) {
    lineTracer.run(ncp);
    // １区間終わるごとに音を奏でる．
    controller.speakerPlayToneFS6(100);
  }
}

/**
 * 現在のisLeftCourse（エッジ）を返すゲッター
 */
bool NormalCourse::getIsLeftCourse() const
{
  return isLeftCourse;
}

/**
 * targetBrightness（カラーセンサの目標値）を返すゲッター
 */
int NormalCourse::getTargetBrightness() const
{
  return targetBrightness;
}
