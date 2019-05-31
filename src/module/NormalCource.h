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
  int currentMovedDistance;
  //! エッジがどっちか． falseが左エッジ，trueが右エッジ
  bool selectedEdge;
public:
  //! コンストラクタ
  NormalCource(Edge& selectedEdge_) : currentMovedDistance(0)
  {
    NormalCource::selectedEdgeLR(selectedEdge_);
  }

/**
 * 左エッジ，右エッジを切り替える．
 * @param Edge::LEFT or, Edge::RIGHT
 */
void selectedEdgeLR(Edge& selectedEdge_);

/**
 * 引数として受け取った距離だけライントレースする．
 * @param 進みたい距離．単位はmm
 */
void  lineTraceForSpecifiedDistance(int specifiedDistance);
};

#endif
