/**
 *  @file   Calibrator.cpp
 *  @brief  キャリブレーションを行うクラス
 *  @author korosuke613
 **/
#include "Calibrator.h"

Calibrator::Calibrator(Controller& con_)
    : con(con_){}

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

  con.tslpTsk(500);
  while (!con.buttonIsPressedEnter()) {
    if (isLeft) {
      std::strcpy(cource,"Left");
    } else {
      std::strcpy(cource,"Right");
    }
    Display::print(3, "Set LRCource: %s ?", cource);

    if (con.buttonIsPressedLeft() || con.buttonIsPressedRight()) {
      isLeft = !isLeft;
      con.speakerPlayToneFS6(50);
      con.tslpTsk(500);
    }
    con.tslpTsk(4);
  }
  Display::print(3, "cource: %s", cource);

  con.speakerPlayToneFS6(100);
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

  con.tslpTsk(500);

  while (1) {
    // ENTERボタンが押されたらループを抜ける
    if(con.buttonIsPressedEnter()) {
      con.speakerPlayToneFS6(100);
      break;
    }

    tmpColor = con.getBrightness();
    Display::print(4, "Set brightness of %s: %3d ?", name, tmpColor);

    con.tslpTsk(4);
  }

  int meanBrightness = 0;
  int times = 10;
  for(int i = 0; i < times; i++) {
    meanBrightness += con.getBrightness();
    con.tslpTsk(4);
  }
  con.speakerPlayToneFS6(200);

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
