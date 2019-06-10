/**
 *  @file   NormalCource.h
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCource.h"

void NormalCource::selectedEdgeLR(Edge& selectedEdge_)
{
  if(selectedEdge_ == Edge::LEFT) {
    selectedEdge = false;
  } else {
    selectedEdge = true;
  }
}

void NormalCource::lineTraceForSpecifiedDistance(std::array<NormalCourceProperty, N> normalCourceProperty)
{
  for(auto& ncp : normalCourceProperty) {
    lineTrace(ncp);
  }
}
