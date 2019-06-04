/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller &controller_)
    : controller(controller_),
      isLeft(true),
      brightnessOfWhite(0),
      brightnessOfBlack(0) {}

bool Calibrator::calibration() {
  Display::print(2, "now calibration...");
  if (!setLRCource()) {
    Display::print(2, "Error setLRCource!");
    return false;
  }

  if (!setBrightness(Brightness::WHITE)) {
    Display::print(2, "Error setBrightness White!");
    return false;
  }

  if (!setBrightness(Brightness::BLACK)) {
    Display::print(2, "Error setBrightness Black!");
    return false;
  }

  Display::print(4, "White: %3d", brightnessOfWhite);
  Display::print(5, "Black: %3d", brightnessOfBlack);

  return true;
}

bool Calibrator::setLRCource() {
  char cource[8] = "Left";

  controller.tslpTsk(500);
  while (!controller.buttonIsPressedEnter()) {
    if (isLeft) {
      std::strcpy(cource, "Left");
    } else {
      std::strcpy(cource, "Right");
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

bool Calibrator::setBrightness(Brightness brightness) {
  char name[8] = "none";

  if (brightness == Brightness::WHITE) {
    std::strcpy(name, "White");
  } else if (brightness == Brightness::BLACK) {
    std::strcpy(name, "Black");
  } else {
    return false;
  }

  controller.tslpTsk(500);

  while (1) {
    // ENTERボタンが押されたらループを抜ける
    if (controller.buttonIsPressedEnter()) {
      controller.speakerPlayToneFS6(100);
      break;
    }

    int tmpColor = controller.getBrightness();
    Display::print(4, "Set brightness of %s: %3d ?", name, tmpColor);

    controller.tslpTsk(4);
  }

  // 4ms毎に10回明るさを取得して、その平均値をメンバ変数に代入する処理
  int meanBrightness = 0;
  int times = 10;
  for (int i = 0; i < times; i++) {
    meanBrightness += controller.getBrightness();
    controller.tslpTsk(4);
  }
  controller.speakerPlayToneFS6(200);

  if (brightness == Brightness::WHITE) {
    brightnessOfWhite = meanBrightness / times;
  } else {
    brightnessOfBlack = meanBrightness / times;
  }

  return true;
}

bool Calibrator::isLeftCource() { return isLeft; }
int Calibrator::getWhiteBrightness() { return brightnessOfWhite; };
int Calibrator::getBlackBrightness() { return brightnessOfBlack; };
