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
  TURN180_DETOUR_RIGHT,
  TURN180_DETOUR_LEFT,
  PUT,
  SPIN_RIGHT45,
  SPIN_LEFT45,
  SPIN_RIGHT135,
  SPIN_LEFT135,
  MOVE_NODE,
  MOVE_DIAGONAL,
  QUICK_PUT_R,
  QUICK_PUT_L
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