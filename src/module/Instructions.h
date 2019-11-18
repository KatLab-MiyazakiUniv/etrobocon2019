/**
 *  @file   Instructions.h
 *  @brief  BlockBingoクラスで使用する
 *  @author Oiwane
 */
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <array>
#include <map>

enum class Order {
  ENTER_BINGO_AREA_L4,
  ENTER_BINGO_AREA_L6,
  SPIN_RIGHT,
  SPIN_LEFT,
  SPIN180,
  STRAIGHT,
  STRAIGHT_DETOUR_RIGHT,
  STRAIGHT_DETOUR_LEFT,
  TURN_RIGHT90_EXIST_BLOCK,
  TURN_RIGHT90_UNEXIST_BLOCK,
  TURN_LEFT90_EXIST_BLOCK,
  TURN_LEFT90_UNEXIST_BLOCK,
  TURN180,
  PUT,
  MOVE_NODE,
  ENTER_BINGO_AREA_R5,
  ENTER_BINGO_AREA_R8,
  QUICK_PUT_R,
  QUICK_PUT_L,
  PREPARE_TO_PUT,
  STRAIGHT_STRAIGHT,
  QUIT
};

class Instructions {
 private:
  std::map<char, Order> mp;

 public:
  /**
   * コンストラクタ
   */
  Instructions();
  /**
   * @brief 受け取った文字列を命令に変換する
   * @param key [mpの添え字]
   */
  Order translate(char key);
};

#endif