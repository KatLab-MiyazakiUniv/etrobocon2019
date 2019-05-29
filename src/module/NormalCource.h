/**
 *  @file   NormalCource.h
 *  @brief  NormalCourceを走る
 *  @author Tatsumi Nishida
 */
#ifndef NORMALCOURCE_H
#define NORMALCOURCE_H

class NormalCource
{
private:
  /* data */
public:
//! コンストラクタ
NormalCource();

//! Lコース，Rコースのエッジを切り替える
void selectedEdgeLR(); 
//! 引数として受け取った距離だけ進む．単位はmm
void  lineTraceForSpecifiedDistance(int distance);
};

#endif
