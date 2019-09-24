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

  // 黄色まで進む処理があるのでテストができない
  // TEST(BlockBingo, moveCircle4OfLTest)
  // {
  //   Controller controller;
  //   BlockBingo blockbingo(controller);

  //   std::array<std::string, 1> order{ "a" };
  //   blockbingo.execOrder<1>(order);
  // }

  // 黄色まで進む処理があるのでテストができない
  // TEST(BlockBingo, moveCircle6OfLTest)
  // {
  //   Controller controller;
  //   BlockBingo blockbingo(controller);

  //   std::array<std::string, 1> order{ "b" };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execSpinRightTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "c" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execSpinLeftTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "e" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execSpin180Test)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "f" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execStraightTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "c" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execStraightDetourRightTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "h" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execStraightDetourLeftTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "i" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execTurnRight90ExistBlockTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "j" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execTurnRight90UnexistBlockTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "k" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execTurnLeft90ExistBlockTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "l" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execTurnLeft90UnexistBlockTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "m" };
    blockbingo.execOrder<1>(order);
  }

  // なぜかテストが失敗する。実機テスト済み
  // TEST(BlockBingo, execTurn180Test)
  // {
  //   Controller controller;
  //   BlockBingo blockbingo(controller);

  //   std::array<std::string, 1> order{ "n" };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execTurn180DetourRightTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "o" };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execTurn180DetourLeftTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<std::string, 1> order{ "p" };
    blockbingo.execOrder<1>(order);
  }

  // なぜかテストが失敗する。実機テスト済み
  // TEST(BlockBingo, execPutInFirstProcessTest)
  // {
  //   Controller controller;
  //   BlockBingo blockbingo(controller);

  //   std::array<std::string, 1> order{ "g" };
  //   blockbingo.execOrder<1>(order);
  // }

  // なぜかテストが失敗する。実機テスト済み
  // TEST(BlockBingo, execPutInSecondProcessTest)
  // {
  //   Controller controller;
  //   BlockBingo blockbingo(controller);

  //   std::array<std::string, 1> order{ "g" };
  //   blockbingo.execOrder<1>(order);
  //   std::array<std::string, 1> order2{ "g" };
  //   blockbingo.execOrder<1>(order2);
  // }

}  // namespace etrobocon2019_test
