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
  constexpr int arraySize = 13;
  int baseSpeed = 640;
  std::array<NormalCourseProperty, arraySize> normalCourseProperty
      /**
       * 詳しく見たいならLineTracer.hを見てね．
       * 進む距離，目標スピード，スピードpid，ターンpid
       */
      = { {         
         { 600, baseSpeed, { 0.1, 0.0, 0.0 }, { 0.9, 0.01, 0.06 } },  // 第1区間
         { 800, 600, { 0.1, 0.0, 0.0 }, { 0.9, 0.0, 0.07 } },         // 第2区間
         { 1300, baseSpeed, { 0.1, 0.0, 0.0 }, { 0.9, 0.0, 0.04 } },  // 第3区間
         { 760, 540, { 0.1, 0.0, 0.0 }, { 0.90, 0.01, 0.07 } },       // 第4区間
         { 740, 520, { 0.1, 0.0, 0.0 }, { 0.90, 0.01, 0.07 } },   // 第5区間
         { 460, 540, { 0.1, 0.0, 0.0 }, { 0.90, 0.01, 0.08 } },  // 第6区間
     /*    { 1230, baseSpeed, { 0.1, 0.0, 0.1 }, { 0.90, 0.01, 0.06 } },  // 第7区間
         { 750, baseSpeed, { 1.8, 0.0, 0.1 }, { 0.9, 0.01, 0.06 } },    // 第8区間
         { 950, 500, { 0.1, 0.0, 0.1 }, { 0.950, 0.01, 0.08 } },  // 第9区間
         { 750, 520, { 0.1, 0.0, 0.1 }, { 1.0, 0.0, 0.09 } },     // 第10区間
         { 1400, 620, { 0.1, 0.0, 0.1 }, { 1.1, 0.0, 0.08 } },    // 第11区間
*/
     /*    { 600, baseSpeed, { 0.1, 0.0, 0.0 }, { 0.8, 0.01, 0.06 } },  // 第1区間
         { 800, baseSpeed, { 0.1, 0.0, 0.0 }, { 0.8, 0.0, 0.07 } },   // 第2区間
         { 1300, baseSpeed, { 0.1, 0.0, 0.0 }, { 0.8, 0.0, 0.04 } },  // 第3区間
         { 760, 580, { 0.1, 0.0, 0.0 }, { 0.80, 0.01, 0.08 } },       // 第4区間
         { 740, 520, { 0.1, 0.0, 0.0 }, { 0.80, 0.01, 0.07 } },  // 第5区間
         { 470, 560, { 0.1, 0.0, 0.0 }, { 0.80, 0.01, 0.08 } },  // 第6区間
     */    { 1290, baseSpeed, { 0.1, 0.0, 0.1 }, { 0.80, 0.01, 0.06 } },  // 第7区間
         { 700, baseSpeed, { 1.8, 0.0, 0.1 }, { 0.8, 0.01, 0.06 } },    // 第8区間
         { 950, 540, { 0.1, 0.0, 0.1 }, { 1.0, 0.01, 0.07 } },  // 第9区間
         { 750, 580, { 0.1, 0.0, 0.1 }, { 1.1, 0.0, 0.08 } },    // 第10区間
         { 1900, 600, { 0.1, 0.0, 0.1 }, { 1.1, 0.01, 0.08 } },   // 第11区間

         { 1500, baseSpeed / 2, { 0.1, 0.0, 0.1 }, { 0.8, 0.0, 0.08 } },          //進入ライン
         { 350, baseSpeed / 4, { 0.1, 0.0, 0.1 }, { 1.1, 0.0, 0.08 } },           //本番で要調整

      } };
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
