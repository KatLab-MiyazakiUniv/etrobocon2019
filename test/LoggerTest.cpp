/**
 * @file   LoggerTest.cpp
 * @brief  LoggerTestクラスのテストファイル
 * @author T.Miyaji
 */
#include <gtest/gtest.h>
#include <fstream>
#include "Logger.h"

namespace etrobocon2019_test {
  TEST(Logger, construct) { Logger logger; }

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
}  // namespace etrobocon2019_test
