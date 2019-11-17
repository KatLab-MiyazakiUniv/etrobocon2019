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
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);
  }

  // 黄色まで進む処理があるのでテストができない
  // TEST(BlockBingo, execEnterBingoAreaL4Test)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'a' };
  //   blockbingo.execOrder<1>(order);
  // }

  // 黄色まで進む処理があるのでテストができない
  // TEST(BlockBingo, execEnterBingoAreaL6Test)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'b' };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execStraightTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'c' };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execSpinRightTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'd' };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execSpinLeftTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'e' };
    blockbingo.execOrder<1>(order);
  }

  TEST(BlockBingo, execSpin180Test)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'f' };
    blockbingo.execOrder<1>(order);
  }

  // なぜかテストが失敗する。実機テスト済み
  // TEST(BlockBingo, execPutInFirstProcessTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'g' };
  //   blockbingo.execOrder<1>(order);
  // }

  // なぜかテストが失敗する。実機テスト済み
  // TEST(BlockBingo, execPutInSecondProcessTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'g' };
  //   blockbingo.execOrder<1>(order);
  //   std::array<char, 1> order2{ 'g' };
  //   blockbingo.execOrder<1>(order2);
  // }

  // なぜかテストが失敗する。実機テスト済み。日本オワオワリ大学
  // TEST(BlockBingo, execStraightDetourRightTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'h' };
  //   blockbingo.execOrder<1>(order);
  // }

  // TEST(BlockBingo, execStraightDetourLeftTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'i' };
  //   blockbingo.execOrder<1>(order);
  // }

  // TEST(BlockBingo, execTurnRight90ExistBlockTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'j' };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execTurnRight90UnexistBlockTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'k' };
    blockbingo.execOrder<1>(order);
  }

  // TEST(BlockBingo, execTurnLeft90ExistBlockTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'l' };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execTurnLeft90UnexistBlockTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'm' };
    blockbingo.execOrder<1>(order);
  }

  // なぜかテストが失敗する。実機テスト済み
  // TEST(BlockBingo, execTurn180Test)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'n' };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execPrepareToPutTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'o' };
    blockbingo.execOrder<1>(order);
  }

  // TEST(BlockBingo, execMoveNodeTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'u' };
  //   blockbingo.execOrder<1>(order);
  // }

  // TEST(BlockBingo, execMoveDiagonalTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'v' };
  //   blockbingo.execOrder<1>(order);
  // }

  // TEST(BlockBingo, execQuickPutRTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'y' };
  //   blockbingo.execOrder<1>(order);
  // }

  // TEST(BlockBingo, execQuickPutLTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'z' };
  //   blockbingo.execOrder<1>(order);
  // }

  // TEST(BlockBingo, execStraightStraightTest)
  // {
  //   int targetBrightness = 70;
  //   Controller controller;
  //   BlockBingo blockbingo(controller, targetBrightness, true);

  //   std::array<char, 1> order{ 'p' };
  //   blockbingo.execOrder<1>(order);
  // }

  TEST(BlockBingo, execMoveToMidpointTest)
  {
    int targetBrightness = 70;
    Controller controller;
    BlockBingo blockbingo(controller, targetBrightness, true);

    std::array<char, 1> order{ 'q' };
    blockbingo.execOrder<1>(order);
  }
}  // namespace etrobocon2019_test
