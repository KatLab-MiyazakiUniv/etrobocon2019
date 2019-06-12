#include "EtRobocon2019.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "NormalCourse.h"

void EtRobocon2019::start()
{
  Controller controller;
  Calibrator calibrator(controller);
  // キャリブレーションする．
	calibrator.calibration();

  // コースと、カラーセンサー目標値の設定
  bool isRightCourse = calibrator.isLeftCource();
  // 黒と白を足して2で割る．
  int targetBrightness = (calibrator.getWhiteBrightness() + calibrator.getBlackBrightness()) / 2;
  // 右ボタンが押されるまで待つ（これを書かないと自動で走り出す．）
  while(!controller.buttonIsPressedRight()) {
  }

  NormalCourse normalCourse(controller, targetBrightness);
  // エッジを指定する．（すると走り出す！！）
  normalCourse.selectedEdgeLR(isRightCourse);
}
