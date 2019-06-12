/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCourse.h"

/** コンストラクタ
 *  @param selectedEdge_  [Leftコースである場合True]
 *  @param targetBrightness_ [カラーセンサーの目標値]
 */
NormalCourse::NormalCourse(bool selectedEdge_, int targetBrightness_)
  : selectedEdge(selectedEdge_),
    targetBrightness(targetBrightness_),
    lineTracer(targetBrightness, selectedEdge)
{
}

void NormalCourse::selectedEdgeLR(bool selectedEdge_)
{
  selectedEdge = selectedEdge_;
  NormalCourse::runNormalCourse();
}

template <typename std::size_t N>
void NormalCourse::lineTraceForSpecifiedDistance(std::array<NormalCourseProperty, N>& ncpArray)
{
  for(auto& ncp : ncpArray) {
    lineTracer.run(ncp);
  }
}

// void NormalCourse::lineTraceForSpecifiedDistance(NormalCourseProperty& normalCourseProperty)
// {
//   lineTracer.run(normalCourseProperty);
// }

void NormalCourse::runNormalCourse()
{
  // ここにパラメータを頑張って書く．
  // 配列の個数
  const int arraySize = 5;
  std::array<PidParameter, arraySize> speedPid = { { { 0.1, 0.2, 0.3 },
                                                     { 0.4, 0.5, 0.6 },
                                                     { 0.7, 0.8, 0.9 },
                                                     { 1.0, 1.1, 1.2 },
                                                     { 1.3, 1.4, 1.5 } } };
  std::array<PidParameter, arraySize> turnPid = { { { 1.6, 1.7, 1.8 },
                                                    { 1.9, 2.0, 2.1 },
                                                    { 2.2, 2.3, 2.4 },
                                                    { 2.5, 2.5, 2.6 },
                                                    { 2.7, 2.8, 2.9 } } };
  std::array<NormalCourseProperty, arraySize> normalCourseProperty = { {
      { 101, 102, speedPid[0], turnPid[0] },
      { 103, 104, speedPid[1], turnPid[1] },
      { 105, 106, speedPid[2], turnPid[2] },
      { 107, 108, speedPid[3], turnPid[3] },
      { 109, 110, speedPid[4], turnPid[4] },
  } };
  lineTraceForSpecifiedDistance(normalCourseProperty);
  // lineTraceForSpecifiedDistance();
}
