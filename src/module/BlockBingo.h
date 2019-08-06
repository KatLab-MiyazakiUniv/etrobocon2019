/**
 *  @file   BlockBingo.h
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#ifndef BLOCKBINGO_H
#define BLOCKBINGO_H

#include <array>
#include <functional>
#include "Controller.h"
#include "Navigator.h"

enum class Order { MOVE, SPIN, COLOR };

/**
 * execOrderで使用する構造体
 *
 * paramValueまたはparamColorを使用しないときは何か値を入れておく
 */
struct OrderProperty {
  Order orderName;    //命令の内容
  double paramValue;  // Navigator.spinの引数で使用する
  Color paramColor;   // Navigator.moveToSpecifiedColorの引数で使用する
};

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

  /**
   * パソコンから受け取ったリストの通りに処理を実行する
   * @param propertys [命令の情報のリスト]
   */
  template <int N>
  void execOrder(std::array<OrderProperty, N>& propertys)
  {
    Navigator navigator(controller);

    for(OrderProperty property : propertys) {
      if(property.orderName == Order::MOVE) {
        navigator.move(350.0, 10);
      } else if(property.orderName == Order::COLOR) {
        navigator.moveToSpecifiedColor(property.paramColor, 10);
      } else if(property.orderName == Order::SPIN) {
        navigator.spin(property.paramValue, (property.paramValue > 0));
      } else {
        controller.stopMotor();
        controller.speakerPlayToneFS6(100);
      }
    }
  }
};

#endif