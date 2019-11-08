/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& controller_)
  : controller(controller_),
    isCameraMode(true),
    isLeft(true){}

bool Calibrator::calibration()
{
  Display::print(2, "Adjust the arm position...");
  this->setArm();
  Display::print(2, "Calibration...");

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

  Display::print(5, "Calibration was completed!");

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

    int r, g, b;
    controller.getRawColor(r, g, b);
    Display::print(4, "R:%3d, G:%3d, B:%3d", r, g, b);

    controller.tslpTsk(4);
  }

  controller.speakerPlayToneFS6(200);

  if(brightness == Brightness::WHITE) {
    rgb_raw_t standardWhite;
    controller.colorSensor.getRawColor(standardWhite);
    controller.setStandardWhite(standardWhite);
  } else {
    rgb_raw_t standardBlack;
    controller.colorSensor.getRawColor(standardBlack);
    controller.setStandardBlack(standardBlack);
  }

  return true;
}

bool Calibrator::getCameraMode() const
{
  return isCameraMode;
}

bool Calibrator::isLeftCourse() const
{
  return isLeft;
}

void Calibrator::setArm()
{
  while(!controller.touchSensor.isPressed()) {
    controller.tslpTsk(4);
  }
  controller.moveArm(50);
  controller.stopLiftMotor();
  controller.moveArm(-20);
}