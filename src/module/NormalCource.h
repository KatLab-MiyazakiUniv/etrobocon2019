/**
 *  @file   NormalCource.h
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURCE_H
#define NORMALCOURCE_H

enum struct Edge {LEFT, RIGHT};

class NormalCource
{
private:
  //! 現在進んだ距離．単位はmm
  int current_moved_distance;
  //! エッジがどっちか． falseが左エッジ，trueが右エッジ
  bool selected_edge;
public:
  //! コンストラクタ
  NormalCource(Edge selected_edge_) : current_moved_distance(0)
  {
    NormalCource::selectedEdgeLR(selected_edge_);
  }

/**
 * Lコース，Rコースのエッジを切り替える．
 * @param Edge::LEFT or, Edge::RIGHT
 */
void selectedEdgeLR(Edge selected_edge_ = Edge::LEFT); 

/**
 * 引数として受け取った距離だけ進む．
 * @param 進みたい距離．単位はmm
 */
void  lineTraceForSpecifiedDistance(int specified_distance);
};

#endif
