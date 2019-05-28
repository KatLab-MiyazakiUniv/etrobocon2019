/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 NormalCourseTest.cpp ../src/NormalCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "EtRobocon2019.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  class EtRobocon2019Test : public ::testing::Test {
    friend class EtRobocon2019;

   protected:
    virtual void SetUp() {}
    EtRobocon2019 et;
  };

  TEST_F(EtRobocon2019Test, startTest)
  {
  }
}  // namespace etrobocon2018_test