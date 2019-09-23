/**
 *  @file   BlockBingo.h
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#ifndef BLOCKBINGO_H
#define BLOCKBINGO_H

#include <array>
#include <map>
#include "Controller.h"
#include "Navigator.h"

enum class Order {
  ENTER_BINGO_AREA_L4,
  ENTER_BINGO_AREA_L6,
  SPIN_RIGHT90,
  SPIN_LEFT90,
  SPIN180,
  STRAIGHT,
  STRAIGHT_DETOUR_RIGHT,
  STRAIGHT_DETOUR_LEFT,
  TURN_RIGHT90_EXIST_BLOCK,
  TURN_RIGHT90_UNEXIST_BLOCK,
  TURN_LEFT90_EXIST_BLOCK,
  TURN_LEFT90_UNEXIST_BLOCK,
  TURN180,
  TURN_RIGHT180,
  TURN_LEFT180,
  PUT,
};

class BlockBingo {
 private:
  Controller& controller;
  //交点サークルから中点までの距離
  const double length;
  // FirstProcess = ブロックサークル内の黒ブロックをボーナスサークル内に設置する
  bool isFirstProcess;
  std::map<std::string, Order> mp;

  //ここからのprivate関数の詳細はモデルの2.2を参照
  /**
   * SPIN_RIGHT90の命令を実行する
   * @brief 90度右に回頭する
   */
  void execSpinRight90();
  /**
   * SPIN_LEFT90の命令を実行する
   * @brief 90度左に回頭する
   */
  void execSpinLeft90();
  /**
   * SPIN180の命令を実行する
   * @brief 180度回頭する
   */
  void execSpin180();
  /**
   * STRAIGHTの命令を実行する
   * @brief
   * 進行方向にブロックがない場合に使用する。ある交点サークルから隣接する交点サークルの距離の分だけ移動する
   */
  void execStraight();
  /**
   * STRAIGHT_DETOUR_RIGHTの命令を実行する
   * @brief 進行方向にブロックがある場合に使用する。右に迂回するように直進する
   */
  void execStraightDetourRight();
  /**
   * STRAIGHT_DETOUR_RIGHTの命令を実行する
   * @brief 進行方向にブロックがある場合に使用する。左に迂回するように直進する
   */
  void execStraightDetourLeft();
  /**
   * TURN_RIGHT90_EXIST_BLOCKの命令を実行する
   * @brief ブロックのある交点サークルで右に90度曲がる。
   */
  void execTurnRight90ExistBlock();
  /**
   * TURN_RIGHT90_UNEXIST_BLOCKの命令を実行する
   * @brief ブロックのない交点サークルで右に90度曲がる。
   */
  void execTurnRight90UnexistBlock();
  /**
   * TURN_LEFT90_EXIST_BLOCKの命令を実行する
   * @brief ブロックのある交点サークルで左に90度曲がる。
   */
  void execTurnLeft90ExistBlock();
  /**
   * TURN_LEFT90_UNEXIST_BLOCKの命令を実行する
   * @brief ブロックのない交点サークルで左に90度曲がる。
   */
  void execTurnLeft90UnexistBlock();
  /**
   * TURN180の命令を実行する
   * @brief ブロックがない場合に使用される。中点で180度旋回してから交点サークルまで直進する
   */
  void execTurn180();
  /**
   * TURN_RIGHT180の命令を実行する
   * @brief ブロックがある場合に使用される。中点で180度旋回してから右に迂回して直進する
   */
  void execTurnRight180();
  /**
   * TURN_RIGHT180の命令を実行する
   * @brief ブロックがある場合に使用される。中点で180度旋回してから左に迂回して直進する
   */
  void execTurnLeft180();
  /**
   * PUTの命令を実行する
   * @brief アームを上げ下げしてブロックをブロックサークルに設置する
   */
  void execPut();

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
   * Lコースのブロックビンゴのブロックサークル6に移動する
   * @brief Lコースのブロックビンゴ開始点からブロックサークル6の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル6の中央まで移動する。
   */
  void moveCircle6OfL();
  /**
   * 命令に使用するマップを初期化する
   */
  void initMap();
  /**
   * パソコンから受け取ったリストの通りに処理を実行する
   * @param orders [命令の情報のリスト]
   */
  template <int N>
  void execOrder(std::array<std::string, N>& orders)
  {
    for(const auto& orderKey : orders) {
      decltype(mp)::iterator it = mp.find(orderKey);
      if(it->second == Order::ENTER_BINGO_AREA_L4) {
        this->moveCircle4OfL();
      } else if(it->second == Order::ENTER_BINGO_AREA_L6) {
        this->moveCircle6OfL();
      } else if(it->second == Order::SPIN_RIGHT90) {
        this->execSpinRight90();
      } else if(it->second == Order::SPIN_LEFT90) {
        this->execSpinLeft90();
      } else if(it->second == Order::SPIN180) {
        this->execSpin180();
      } else if(it->second == Order::STRAIGHT) {
        this->execStraight();
      } else if(it->second == Order::STRAIGHT_DETOUR_RIGHT) {
        this->execStraightDetourRight();
      } else if(it->second == Order::STRAIGHT_DETOUR_LEFT) {
        this->execStraightDetourLeft();
      } else if(it->second == Order::TURN_RIGHT90_EXIST_BLOCK) {
        this->execTurnRight90ExistBlock();
      } else if(it->second == Order::TURN_RIGHT90_UNEXIST_BLOCK) {
        this->execTurnRight90UnexistBlock();
      } else if(it->second == Order::TURN_LEFT90_EXIST_BLOCK) {
        this->execTurnLeft90ExistBlock();
      } else if(it->second == Order::TURN_LEFT90_UNEXIST_BLOCK) {
        this->execTurnLeft90UnexistBlock();
      } else if(it->second == Order::TURN180) {
        this->execTurn180();
      } else if(it->second == Order::TURN_RIGHT180) {
        this->execTurnRight180();
      } else if(it->second == Order::TURN_LEFT180) {
        this->execTurnLeft180();
      } else if(it->second == Order::PUT) {
        this->execPut();
      }
    }
  }
};

#endif