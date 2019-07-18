/**
 *  @file   BlockBingo.cpp
 *  @brief  BlockBingoクラスのテストファイル
 *  @author Oiwane
 */
#include "BlockBingo.h"

namespace etrobocon2019_test {

  TEST(BlockBingo, init)
  {
    Controller controller;
    Blockbingo blockbing(controller);
  }

  TEST(BlockBingo, moveCircle4OfLTEST)
  {
    Controller controller;
    Blockbingo blockbingo(controller);

    blockbingo.moveCircle4OfL();
  }
}  // namespace etrobocon2019_test
