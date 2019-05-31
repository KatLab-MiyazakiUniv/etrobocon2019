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
  NormalCource(Edge& selected_edge_) : current_moved_distance(0)
  {
    NormalCource::selectedEdgeLR(selected_edge_);
  }

/**
 * 左エッジ，右エッジを切り替える．
 * @param Edge::LEFT or, Edge::RIGHT
 */
void selectedEdgeLR(Edge& selected_edge_);

/**
 * 引数として受け取った距離だけライントレースする．
 * @param 進みたい距離．単位はmm
 */
void  lineTraceForSpecifiedDistance(int specified_distance);
};

#endif
