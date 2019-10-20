#include "EtRobocon2019.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2019_test {

  class EtRobocon2019Test : public ::testing::Test {
    friend class EtRobocon2019;

   protected:
    virtual void SetUp() {}
    EtRobocon2019 et;
  };

  TEST_F(EtRobocon2019Test, startTest) {}
}  // namespace etrobocon2019_test