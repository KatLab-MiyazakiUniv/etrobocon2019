/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& controller_)
  : controller(controller_),
    isCameraMode(true),
    isLeft(true),
    brightnessOfWhite(0),
    brightnessOfBlack(0)
{
}

bool Calibrator::calibration()
{
  Display::print(2, "Please push left touch sensor...");
  this->setArm();
  Display::print(2, "now calibration...");

  if(!setCameraMode()) {
    Display::print(2, "Error setCameraMode!");
    return false;
  }

  if(!setLRCourse()) {
    Display::print(2, "Error setLRCourse!");
    return false;
  }

  if(!setBrightness(Brightness::WHITE)) {
    Display::print(2, "Error setBrightness White!");
    return false;
  }

  if(!setBrightness(Brightness::BLACK)) {
    Display::print(2, "Error setBrightness Black!");
    return false;
  }

  Display::print(5, "White: %3d", brightnessOfWhite);
  Display::print(6, "Black: %3d", brightnessOfBlack);

  return true;
}

bool Calibrator::setCameraMode()
{
  char cameraMode[8] = "ON";

  controller.tslpTsk(500);
  while(!controller.buttonIsPressedEnter()) {
    if(isCameraMode) {
      std::strcpy(cameraMode, "ON");
    } else {
      std::strcpy(cameraMode, "OFF");
    }
    Display::print(3, "camera system: %s ?", cameraMode);
    int r, g, b;
    controller.getRawColor(r, g, b);
    Display::print(4, "R:%3d, G:%3d, B:%3d", r, g, b);

    if(controller.buttonIsPressedLeft() || controller.buttonIsPressedRight()) {
      isCameraMode = !isCameraMode;
      controller.speakerPlayToneFS6(50);
      controller.tslpTsk(500);
    }
    controller.tslpTsk(4);
  }
  Display::print(3, "camera system: %s", cameraMode);

  controller.speakerPlayToneFS6(100);
  return true;
}

bool Calibrator::setLRCourse()
{
  char course[8] = "Left";

  controller.tslpTsk(500);
  while(!controller.buttonIsPressedEnter()) {
    if(isLeft) {
      std::strcpy(course, "Left");
    } else {
      std::strcpy(course, "Right");
    }
    Display::print(4, "Set LRCourse: %s ?", course);

    if(controller.buttonIsPressedLeft() || controller.buttonIsPressedRight()) {
      isLeft = !isLeft;
      controller.speakerPlayToneFS6(50);
      controller.tslpTsk(500);
    }
    controller.tslpTsk(4);
  }
  Display::print(4, "course: %s", course);

  controller.speakerPlayToneFS6(100);
  return true;
}

bool Calibrator::setBrightness(Brightness brightness)
{
  char name[8] = "none";

  if(brightness == Brightness::WHITE) {
    std::strcpy(name, "White");
  } else if(brightness == Brightness::BLACK) {
    std::strcpy(name, "Black");
  } else {
    return false;
  }

  controller.tslpTsk(500);

  while(1) {
    // ENTERボタンが押されたらループを抜ける
    if(controller.buttonIsPressedEnter()) {
      controller.speakerPlayToneFS6(100);
      break;
    }

    int tmpColor = controller.getBrightness();
    Display::print(5, "Set brightness of %s: %3d ?", name, tmpColor);

    controller.tslpTsk(4);
  }

  controller.speakerPlayToneFS6(200);

  if(brightness == Brightness::WHITE) {
    brightnessOfWhite = averageBrightness();
  } else {
    brightnessOfBlack = averageBrightness();
  }

  return true;
}

int Calibrator::averageBrightness()
{
  // 4ms毎に10回明るさを取得して、その平均値をメンバ変数に代入する処理
  int meanBrightness = 0;
  int times = 10;
  for(int i = 0; i < times; i++) {
    meanBrightness += controller.getBrightness();
    controller.tslpTsk(4);
  }

  return meanBrightness / times;
}

bool Calibrator::getCameraMode() const
{
  return isCameraMode;
}

bool Calibrator::isLeftCourse() const
{
  return isLeft;
}

int Calibrator::getWhiteBrightness() const
{
  return brightnessOfWhite;
};

int Calibrator::getBlackBrightness() const
{
  return brightnessOfBlack;
};

void Calibrator::setArm()
{
  while(!controller.touchSensor.isPressed()) {
    controller.tslpTsk(4);
  }
  controller.moveArm(50);
  controller.stopLiftMotor();
  controller.moveArm(-20);
}