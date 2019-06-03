/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& controller_)
    : controller(controller_){}

bool Calibrator::calibration() {
  Display::print(2, "now calibration...");
  isFinish = false;

  isFinish = setLRCource();
  isFinish = setBrightness(Brightness::WHITE);
  isFinish = setBrightness(Brightness::BLACK);
  Display::print(4, "White: %3d", brightnessOfWhite);
  Display::print(5, "Black: %3d", brightnessOfBlack);

  return isFinish;
}

bool Calibrator::setLRCource() {
  char cource[8] = "Left";

  controller.tslpTsk(500);
  while (!controller.buttonIsPressedEnter()) {
    if (isLeft) {
      std::strcpy(cource,"Left");
    } else {
      std::strcpy(cource,"Right");
    }
    Display::print(3, "Set LRCource: %s ?", cource);

    if (controller.buttonIsPressedLeft() || controller.buttonIsPressedRight()) {
      isLeft = !isLeft;
      controller.speakerPlayToneFS6(50);
      controller.tslpTsk(500);
    }
    controller.tslpTsk(4);
  }
  Display::print(3, "cource: %s", cource);

  controller.speakerPlayToneFS6(100);
  return true;
}

bool Calibrator::setBrightness(Brightness b) { 
  int tmpColor = 0;
  char name[8] = "none";

  if(b == Brightness::WHITE){
    std::strcpy(name, "White");
  }else if(b == Brightness::BLACK){
    std::strcpy(name, "Black");
  }else{
    return false;
  }

  controller.tslpTsk(500);

  while (1) {
    // ENTERボタンが押されたらループを抜ける
    if(controller.buttonIsPressedEnter()) {
      controller.speakerPlayToneFS6(100);
      break;
    }

    tmpColor = controller.getBrightness();
    Display::print(4, "Set brightness of %s: %3d ?", name, tmpColor);

    controller.tslpTsk(4);
  }

  int meanBrightness = 0;
  int times = 10;
  for(int i = 0; i < times; i++) {
    meanBrightness += controller.getBrightness();
    controller.tslpTsk(4);
  }
  controller.speakerPlayToneFS6(200);

  if(b == Brightness::WHITE){
    brightnessOfWhite = meanBrightness / times;
  }else{
    brightnessOfBlack = meanBrightness / times;
  }

  return true;
}

bool Calibrator::isLeftCource() { return isLeft; }
int Calibrator::getWhiteBrightness() { return brightnessOfWhite; };
int Calibrator::getBlackBrightness() { return brightnessOfBlack; };
