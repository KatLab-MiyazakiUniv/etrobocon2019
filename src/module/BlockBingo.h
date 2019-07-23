/**
 *  @file   BlockBingo.h
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#ifndef BLOCKBINGO_H
#define BLOCKBINGO_H

#include "Controller.h"
#include "Navigator.h"

class BlockBingo {
 private:
  Controller& controller;

 public:
  /**
   * コンストラクタ
   * @param controller_ [Controllerの参照]
   */
  explicit BlockBingo(Controller& controller_);

  /**
   * Lコースのブロックビンゴのブロックサークル4に移動する
   * @brief Lコースのブロックビンゴ開始点からブロックサークル4の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル4の中央まで移動する。
   */
  void moveCircle4OfL();
};

#endif