#include "EtRobocon2019.h"
#include "BlockBingo.h"
#include "Bluetooth.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "NormalCourse.h"
#include "Navigator.h"
#include "Parking.h"

void EtRobocon2019::start()
{
  Controller controller;
  Calibrator calibrator(controller);
  // キャリブレーションする．
  calibrator.calibration();

  // コースと、カラーセンサー目標値の設定
  bool isLeftCourse = calibrator.isLeftCourse();
  // 黒と白を足して2で割る．
  int targetBrightness = (calibrator.getWhiteBrightness() + calibrator.getBlackBrightness()) / 2;
  // タッチセンサーが押されるまで待つ（これを書かないと自動で走り出す．）
  while(!controller.touchSensor.isPressed()) {
    controller.tslpTsk(4);
  }
  Bluetooth::is_start = true;

  NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
  // NormalCourseを走り出す．
  normalCourse.runNormalCourse();

  // ブロックビンゴ
  BlockBingo blockBingo(controller, targetBrightness);
  // ここでビンゴを開始するblockBingoのメンバ関数を呼び出す
  blockBingo.execOrder<256>(Bluetooth::commands);

  // ガレージ
  Parking parking(controller, targetBrightness);
  if(isLeftCourse) {
    parking.parkAtAL();
  } else {
    parking.parkAtAR();
  }
}
