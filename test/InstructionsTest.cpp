/**
 *  @file   Instructions.cpp
 *  @brief  Instructionsクラスのテストファイル
 *  @author Oiwane
 */
#include <gtest/gtest.h>
#include "Instructions.h"

namespace etrobocon2019_test {

  TEST(Instructions, init) { Instructions instructions; }

  TEST(Instructions, translateTest)
  {
    Instructions instructions;

    ASSERT_EQ(Order::ENTER_BINGO_AREA_L4, instructions.translate('a'));
    ASSERT_EQ(Order::ENTER_BINGO_AREA_L6, instructions.translate('b'));
    ASSERT_EQ(Order::STRAIGHT, instructions.translate('c'));
    ASSERT_EQ(Order::SPIN_RIGHT, instructions.translate('d'));
    ASSERT_EQ(Order::SPIN_LEFT, instructions.translate('e'));
    ASSERT_EQ(Order::SPIN180, instructions.translate('f'));
    ASSERT_EQ(Order::PUT, instructions.translate('g'));
    ASSERT_EQ(Order::STRAIGHT_DETOUR_RIGHT, instructions.translate('h'));
    ASSERT_EQ(Order::STRAIGHT_DETOUR_LEFT, instructions.translate('i'));
    ASSERT_EQ(Order::TURN_RIGHT90_EXIST_BLOCK, instructions.translate('j'));
    ASSERT_EQ(Order::TURN_RIGHT90_UNEXIST_BLOCK, instructions.translate('k'));
    ASSERT_EQ(Order::TURN_LEFT90_EXIST_BLOCK, instructions.translate('l'));
    ASSERT_EQ(Order::TURN_LEFT90_UNEXIST_BLOCK, instructions.translate('m'));
    ASSERT_EQ(Order::TURN180, instructions.translate('n'));

    ASSERT_EQ(Order::PREPARE_TO_PUT, instructions.translate('o'));
    ASSERT_EQ(Order::STRAIGHT_STRAIGHT, instructions.translate('p'));
    ASSERT_EQ(Order::MOVE_TO_MIDPOINT, instructions.translate('q'));
    ASSERT_EQ(Order::MOVE_NODE, instructions.translate('u'));

    ASSERT_EQ(Order::ENTER_BINGO_AREA_R5, instructions.translate('w'));
    ASSERT_EQ(Order::ENTER_BINGO_AREA_R8, instructions.translate('x'));

    ASSERT_EQ(Order::QUICK_PUT_R, instructions.translate('y'));
    ASSERT_EQ(Order::QUICK_PUT_L, instructions.translate('z'));
  }
}  // namespace etrobocon2019_test