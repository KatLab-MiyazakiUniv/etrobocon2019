/**
 *  @file   NormalCourse.h
 *  @brief  NormalCourseを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCourse.h"

void NormalCourse::selectedEdgeLR(Edge &selectedEdge_)
{
  if (selectedEdge_ == Edge::LEFT)
  {
    selectedEdge = false;
  }
  else
  {
    selectedEdge = true;
  }
}

void NormalCourse::lineTraceForSpecifiedDistance(
    std::array<NormalCourseProperty, N> NormalCourseProperty)
{
  for (auto &ncp : NormalCourseProperty)
  {
    lineTrace(ncp);
  }
}
