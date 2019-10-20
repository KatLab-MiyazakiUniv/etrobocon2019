/**
 *  @file   BlockBingo.h
 *  @brief  ブロックビンゴで使用する動作をまとめたクラス
 *  @author Oiwane
 */
#ifndef BLOCKBINGO_H
#define BLOCKBINGO_H

#include <array>
#include "Controller.h"
#include "Instructions.h"
#include "Navigator.h"

class BlockBingo {
 private:
  Controller& controller;
  // Navigator navigator;
  //交点サークルから中点までの距離
  const int targetBrightness;
  const double length;
  // FirstProcess = ブロックサークル内の黒ブロックをボーナスサークル内に設置する
  bool isFirstProcess;
  const double pGain;
  const int straightPwm;

  //ここからのprivate関数の詳細はモデルの2.2を参照
  /**
   * SPIN_RIGHTの命令を実行する
   * @brief 90度右に回頭する
   */
  void execSpinRight();
  /**
   * SPIN_LEFTの命令を実行する
   * @brief 90度左に回頭する
   */
  void execSpinLeft();
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
  void execTurn180DetourRight();
  /**
   * TURN_RIGHT180の命令を実行する
   * @brief ブロックがある場合に使用される。中点で180度旋回してから左に迂回して直進する
   */
  void execTurn180DetourLeft();
  /**
   * PUTの命令を実行する
   * @brief ブロックをブロックサークルに設置する
   */
  void execPut();
  /**
   * SPIN_RIGHT45の命令を実行する
   * @brief 45度右に回頭する
   */
  void execSpinRight45();
  /**
   * SPIN_LEFT45の命令を実行する
   * @brief 45度左に回頭する
   */
  void execSpinLeft45();
  /**
   * SPIN_RIGHT135の命令を実行する
   * @brief 135度右に回頭する
   */
  void execSpinRight135();
  /**
   * SPIN_LEFT135の命令を実行する
   * @brief 135度左に回頭する
   */
  void execSpinLeft135();
  /**
   * MOVE_NODEの命令を実行する
   * @brief lengthだけ直進する
   */
  void execMoveNode();
  /**
   * MOVE_DIAGONALの命令を実行する
   * @brief 中点から中点まで斜めに移動する
   */
  void execMoveDiagonal();

  void execQuicPutR();

  void execQuicPutL();

public:
  /**
   * コンストラクタ
   * @param controller_ [Controllerの参照]
   */
  BlockBingo(Controller& controller_, int targetBrightness_);

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
   * パソコンから受け取ったリストの通りに処理を実行する
   * @param orders [命令の情報のリスト]
   */
  template <int N>
  void execOrder(std::array<char, N>& orderKeys)
  {
    Instructions instructions;

    for(const auto& orderKey : orderKeys) {
      Order order = instructions.translate(orderKey);

      switch(order) {
        case Order::ENTER_BINGO_AREA_L4:
          this->moveCircle4OfL();
          break;

        case Order::ENTER_BINGO_AREA_L6:
          this->moveCircle6OfL();
          break;

        case Order::SPIN_RIGHT:
          this->execSpinRight();
          break;

        case Order::SPIN_LEFT:
          this->execSpinLeft();
          break;

        case Order::SPIN180:
          this->execSpin180();
          break;

        case Order::STRAIGHT:
          this->execStraight();
          break;

        case Order::STRAIGHT_DETOUR_RIGHT:
          this->execStraightDetourRight();
          break;

        case Order::STRAIGHT_DETOUR_LEFT:
          this->execStraightDetourLeft();
          break;

        case Order::TURN_RIGHT90_EXIST_BLOCK:
          this->execTurnRight90ExistBlock();
          break;

        case Order::TURN_RIGHT90_UNEXIST_BLOCK:
          this->execTurnRight90UnexistBlock();
          break;

        case Order::TURN_LEFT90_EXIST_BLOCK:
          this->execTurnLeft90ExistBlock();
          break;

        case Order::TURN_LEFT90_UNEXIST_BLOCK:
          this->execTurnLeft90UnexistBlock();
          break;

        case Order::TURN180:
          this->execTurn180();
          break;

        case Order::TURN180_DETOUR_RIGHT:
          this->execTurn180DetourRight();
          break;

        case Order::TURN180_DETOUR_LEFT:
          this->execTurn180DetourLeft();
          break;

        case Order::PUT:
          this->execPut();
          break;

        case Order::SPIN_RIGHT45:
          this->execSpinRight45();
          break;

        case Order::SPIN_LEFT45:
          this->execSpinLeft45();
          break;

        case Order::SPIN_RIGHT135:
          this->execSpinRight135();
          break;

        case Order::SPIN_LEFT135:
          this->execSpinLeft135();
          break;

        case Order::MOVE_NODE:
          this->execMoveNode();
          break;

        case Order::MOVE_DIAGONAL:
          this->execMoveDiagonal();
          break;

        default:
          controller.speakerPlayToneFS6(1000);
      }
    }
  }
};

#endif