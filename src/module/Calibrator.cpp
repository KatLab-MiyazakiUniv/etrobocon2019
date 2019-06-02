/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& con_, Display& dis_)
    : con(con_), dis(dis_) {}

bool Calibrator::calibration() {
  dis.print(2, "now calibration...");
  isFinish = false;

  isFinish = setLRCource();
  isFinish = setBrightness(brightnessOfWhite);
  isFinish = setBrightness(brightnessOfWhite);

  return isFinish;
}

bool Calibrator::setLRCource() {
  std::string cource = "Left";

  while (!con.buttonIsPressedEnter()) {
    if (isLeft) {
      cource = "Left";
    } else {
      cource = "Right";
    }

    dis.print(3, "Set LRCource: %s ?", cource.c_str());

    if (con.buttonIsPressedLeft() || con.buttonIsPressedRight()) {
      isLeft = !isLeft;

    }

    con.tslpTsk(4);
  }
}

bool Calibrator::setBrightness(unsigned int color) { return true; }

bool Calibrator::isLeftCource() { return isLeft; }
int Calibrator::getWhiteBrightness() { return brightnessOfWhite; };
int Calibrator::getBlackBrightness() { return brightnessOfBlack; };
