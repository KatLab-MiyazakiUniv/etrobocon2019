/**
 *  @file   NormalCource.cpp
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCource.h"

void NormalCource::selectedEdgeLR(Edge &selectedEdge_) {
  if (selectedEdge_ == Edge::LEFT) {
    selectedEdge = false;
  } else {
    selectedEdge = true;
  }
}

void NormalCource::lineTraceForSpecifiedDistance(
    NormalCourceProperty &normalCourceProperty[]) {
  for (auto &ncp : normalCourceProperty) {
    ncp.speed
  }
}
