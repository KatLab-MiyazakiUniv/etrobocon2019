/**
 *  @file   CalibratorTest.cpp
 *  @brief  Calibratorクラスのテストファイル
 *  @author korosuke613
 **/

/* コンパイル(平木場)
$ g++-8 CalibratorTest.cpp ../src/module/Calibrator.cpp gtest_main.o gtest-all.o
-I../src -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "Calibrator.h"
#include "Controller.h"
#include "Display.h"

namespace etrobocon2019_test {

TEST(Calibrator, init) {
  Controller con;
  Calibrator calibrator(con);

  ASSERT_EQ(calibrator.isLeftCource(), true);
  ASSERT_EQ(calibrator.getWhiteBrightness(), 0);
  ASSERT_EQ(calibrator.getBlackBrightness(), 0);
}

TEST(Calibrator, setLRCourceTest1) {
  Controller con;

  Calibrator calibrator(con);

  calibrator.setLRCource();

  ASSERT_EQ(calibrator.isLeftCource(), true);
}

TEST(Calibrator, setLRCourceTest2) {
  Controller con;

  Calibrator calibrator(con);

  con.pushRight = true;
  calibrator.setLRCource();

  ASSERT_EQ(calibrator.isLeftCource(), false);
}

TEST(Calibrator, setLRCourceTest3) {
  Controller con;

  Calibrator calibrator(con);

  con.pushLeft = true;
  calibrator.setLRCource();

  ASSERT_EQ(calibrator.isLeftCource(), false);
}

TEST(Calibrator, setLRCourceTest4) {
  Controller con;

  Calibrator calibrator(con);

  con.pushLeft = true;
  con.pushRight = true;
  calibrator.setLRCource();
  ASSERT_EQ(calibrator.isLeftCource(), true);
}

TEST(Calibrator, setBrightnessTest1) {
  Controller con;

  Calibrator calibrator(con);

  con.brightness = 100;
  calibrator.setBrightness(Brightness::WHITE);
  ASSERT_EQ(calibrator.getWhiteBrightness(), 100);
}

TEST(Calibrator, setBrightnessTest2) {
  Controller con;

  Calibrator calibrator(con);

  con.brightness = 200;
  calibrator.setBrightness(Brightness::BLACK);
  ASSERT_EQ(calibrator.getBlackBrightness(), 200);
}

TEST(Calibrator, setBrightnessTest3) {
  Controller con;

  Calibrator calibrator(con);
  con.brightness = 120;
  calibrator.setBrightness(Brightness::WHITE);
  ASSERT_EQ(calibrator.getWhiteBrightness(), 120);
  con.brightness = 30;
  calibrator.setBrightness(Brightness::BLACK);
  ASSERT_EQ(calibrator.getBlackBrightness(), 30);
}

TEST(Calibrator, calibrationTest) {
  Controller con;

  Calibrator calibrator(con);
  calibrator.calibration();
}

}  // namespace etrobocon2019_test
