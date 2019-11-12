#include "EtRobocon2019.h"
#include "BlockBingo.h"
#include "Bluetooth.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "NormalCourse.h"
#include "Navigator.h"
#include "Parking.h"
#include "MoveDirectGarage.h"
#include "Distance.h"
#include "Curvature.h"
#include "Logger.h"

void EtRobocon2019::start()
{
  Controller controller;
  controller.speakerSetVolume(100);
  Calibrator calibrator(controller);
  // キャリブレーションする．
  calibrator.calibration();

  // コースと、カラーセンサー目標値の設定
  bool isLeftCourse = calibrator.isLeftCourse();
  // 黒と白を足して2で割る．
  constexpr double targetBrightness = (255 - 0) / 2.0;
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

  //直接ガレージに移動する
  MoveDirectGarage moveDirectGarage(controller, targetBrightness);
  if(isLeftCourse) {
    //ブロックビンゴを実行する処理を記述
  } else {
    moveDirectGarage.moveDirectGarageR();  // Rコースの場合はビンゴを行わずにガレージ駐車を行う
  }

  double distances[] = { 750, 640 };
  double curvatures[] = { 0.0, 0.00255 };
  for(int i = 0; i != 2; ++i) {
    Curvature curvature(curvatures[i], 1.0, 1.8, 0.0);
    Distance distance;
    while(distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount())
          < distances[i]) {
      int turnValue
          = curvature.control(controller.getLeftMotorCount(), controller.getRightMotorCount(), 640);
      controller.setLeftMotorPwm(70 - turnValue);
      controller.setRightMotorPwm(70 + turnValue);

      controller.tslpTsk(4);
    }
  }
}
