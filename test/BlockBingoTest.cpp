/**
 *  @file   BlockBingo.cpp
 *  @brief  BlockBingoクラスのテストファイル
 *  @author Oiwane
 */
#include <gtest/gtest.h>
#include "BlockBingo.h"

namespace etrobocon2019_test {

  TEST(BlockBingo, init)
  {
    Controller controller;
    BlockBingo blockbing(controller);
  }

  TEST(BlockBingo, moveCircle4OfLTEST)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    blockbingo.moveCircle4OfL();
  }
}  // namespace etrobocon2019_test
