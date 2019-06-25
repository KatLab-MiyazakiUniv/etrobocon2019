/**
 * @file   LoggerTest.cpp
 * @brief  Loggerクラスのテストファイル
 * @author T.Miyaji
 */
#include <gtest/gtest.h>
#include <fstream>
#include "Logger.h"

namespace etrobocon2019_test {
  TEST(Logger, construct) { Logger logger; }

  TEST(Logger, construct_fileName)
  {
    Logger logger("log101.csv");  // ファイル名は適当
    // 出力ファイルが存在することを確認する
    std::ifstream ifs("log101.csv");
    ASSERT_TRUE(ifs.is_open());
  }
  TEST(Logger, writeTest)
  {
    Logger logger;
    // ファイルが正しく書き込めることを確認する
    logger.write("%d\n", 123);

    // 出力ファイルが存在することを確認する
    std::ifstream ifs("log.csv");
    ASSERT_TRUE(ifs.is_open());

    // 作成したファイルを削除する
    std::remove("log.csv");
  }

  TEST(Logger, streamTest)
  {
    Logger logger;

    logger << 1 << 2 << 4.3;
    logger << 3;

    // 出力ファイルが存在することを確認する
    std::ifstream ifs("log.csv");
    ASSERT_TRUE(ifs.is_open());

    // 作成したファイルを削除する
    std::remove("log.csv");
  }
}  // namespace etrobocon2019_test
