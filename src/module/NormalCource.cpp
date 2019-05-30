/**
 *  @file   NormalCource.cpp
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#include "NormalCource.h"

void NormalCource::selectedEdgeLR(Edge selected_edge_) {
  if (selected_edge_ == Edge::LEFT) {
    selected_edge = false;
  } else {
    selected_edge = true;
  }
  
}

void NormalCource::lineTraceForSpecifiedDistance(int specified_distance) {
  
}
