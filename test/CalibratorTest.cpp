/**
 *  @file   CalibratorTest.cpp
 *  @brief  Calibratorクラスのテストファイル
 *  @author korosuke613
 **/

/* コンパイル(平木場)
$ g++-8 CalibratorTest.cpp ../src/module/Calibrator.cpp gtest_main.o gtest-all.o -I../src
-I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "Calibrator.h"
#include "Controller.h"
#include "Display.h"

namespace etrobocon2019_test {

TEST(Calibrator, init) {
  Controller con;
  Display dis;
  Calibrator calibrator(con, dis);

  ASSERT_EQ(calibrator.isLeftCource(), true);
  ASSERT_EQ(calibrator.getWhiteBrightness(), 0);
  ASSERT_EQ(calibrator.getBlackBrightness(), 0);
}

TEST(Calibrator, setLRCourceTest1) {
  Controller con;
  Display dis;

  Calibrator calibrator(con, dis);

  calibrator.setLRCource();

  ASSERT_EQ(calibrator.isLeftCource(), true);
}

TEST(Calibrator, setLRCourceTest2) {
  Controller con;
  Display dis;

  Calibrator calibrator(con, dis);

  con.pushRight = true;
  calibrator.setLRCource();

  ASSERT_EQ(calibrator.isLeftCource(), false);
}

TEST(Calibrator, setLRCourceTest3) {
  Controller con;
  Display dis;

  Calibrator calibrator(con, dis);

  con.pushLeft = true;
  calibrator.setLRCource();

  ASSERT_EQ(calibrator.isLeftCource(), false);
}

TEST(Calibrator, setLRCourceTest4) {
  Controller con;
  Display dis;

  Calibrator calibrator(con, dis);

  con.pushLeft = true;
  con.pushRight = true;
  calibrator.setLRCource();
  ASSERT_EQ(calibrator.isLeftCource(), true);
}

}  // namespace etrobocon2019_test
