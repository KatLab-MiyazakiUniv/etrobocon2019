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
    ASSERT_EQ(Order::TURN180_DETOUR_RIGHT, instructions.translate('o'));
    ASSERT_EQ(Order::TURN180_DETOUR_LEFT, instructions.translate('p'));
  }
}  // namespace etrobocon2019_test