/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCourse.h"

void NormalCourse::selectedEdgeLR(bool selectedEdge_)
{
  selectedEdge = selectedEdge_;
  runNormalCourse();
}

void NormalCourse::lineTraceForSpecifiedDistance(
    std::array<NormalCourseProperty, SIZE>& normalCourseProperty)
{
  for(auto& ncp : normalCourseProperty) {
    lineTrace.run(ncp);
  }
}

void NormalCourse::lineTraceForSpecifiedDistance(NormalCourseProperty& normalCourseProperty)
{
  lineTrace.run(normalCourseProperty);
}

void NormalCourse::runNormalCourse()
{
  // ライントレースのインスタンスを生成
  LineTracer lineTrace = LineTrace(selectedEdge, targetBrightness);
  // ここからパラメータを頑張って書く．
  // 配列の個数
  const int size = 8;
  
}
